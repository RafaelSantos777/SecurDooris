#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <BoardCommands.h>

const long MINIMUM_TIME_BETWEEN_SESSIONS = 1L * 60 * 1000;
const int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 100;
const int DEFAULT_MINIMUM_DELAY_TIME = 50;

const int DOOR_OPEN_TIME = 15000;
const int ALARM_TIME = 10000;
const int HAND_WAIT_INPUT_TIME = 2000;
const int FAST_FEEDBACK_TIME = 2000;

const int INPUT_READ_BEEP_TIME = 500;
const int INPUT_ACCEPTED_BEEP_TIME = 100;
const int INPUT_DENIED_BEEP_TIME = 200;

const int ALARM_BUZZ_SOUND = 3000;
const int INPUT_READ_BUZZ_SOUND = 200;
const int INPUT_ACCEPTED_BUZZ_SOUND = 100;
const int INPUT_DENIED_BUZZ_SOUND = 500;

const Color INPUT_ACCEPTED_COLOR = GREEN;
const Color INPUT_DENIED_COLOR = RED;
const Color WAIT_FOR_USER_INPUT_COLOR = BLUE;
const Color ALARM_COLOR = RED;
const Color THINKING_COLOR = YELLOW;
const Color DOOR_OPEN_COLOR = WHITE;

Buzzer buzzer(2);
LightSensor lightSensor(A0); // 5V
RGBLED rgbled(3, 5, 6); // R G(far gnd) B(side G)
HumanSensor humanSensor; // 3.3V or 5V
NfcAdapter nfc(pn532_i2c); // 3.3V or 5V, SCL(A5), SDA(A4)
SecurDoorisServo servo(8); // 5V

// Used to blink of arduino builtin-led everyloop.
// If the led stops blinking, something may have gone wrong.
bool isBuiltInLedOn = false;

/*  Main script logic variables:
    'currentTime'                   - Used along main script to try to synchronize some actions (has been left here, may have no real impact)
    'lastSessionLatestUpdateTime'   - Helps Arduino to know when does it needs to stop and turn off all atuators. It is updated when the user moves, tag is read or arduino receives a commands
    'sessionOpen'                   - Used to tell when a session has changed
    'humanNearby'                   - Used to allow code to run when a human is nearby
    'closing'                       - Stops parts of code that shouldn't run after the Alarm was triggered or the door was opened
    'lastAction'                    - Used to tell when what was the last action (only used once)
*/
long currentTime = 0;
long lastSessionLatestUpdateTime = -MINIMUM_TIME_BETWEEN_SESSIONS;
bool sessionOpen = false;
bool humanNearby = false;
bool closing = false;
int lastAction = 0;


// When not blocked, reads and sends a present tag. Also tells node-red that a new session has started
void checkTag() {
    if (!tagReaderBlocked() && nfc.tagPresent(50)) {
        blockTagReader();
        if (!sessionOpen) {
            sessionOpen = true;
            Serial.println(UPDATE_SESSION);
        }
        buzzer.buzz(INPUT_READ_BUZZ_SOUND, INPUT_READ_BEEP_TIME);
        Serial.println(NFC);
        Serial.println(nfc.read().getUidString());
        lastSessionLatestUpdateTime = currentTime;
        // Wait for Node-red
        rgbled.setColorBlink(THINKING_COLOR, 0, THINKING);
        lastAction = NFC;
    }
}

// functions that creates the feedback of the input done by the user (called according to commands received)
void inputDenied() {
    buzzer.buzz(INPUT_DENIED_BUZZ_SOUND, INPUT_DENIED_BEEP_TIME);
    rgbled.setColor(INPUT_DENIED_COLOR);
    delay(FAST_FEEDBACK_TIME);
}
void inputAccepted() {
    rgbled.setColor(INPUT_ACCEPTED_COLOR);
    buzzer.buzz(INPUT_ACCEPTED_BUZZ_SOUND, INPUT_ACCEPTED_BEEP_TIME);
    delay(FAST_FEEDBACK_TIME);
}

// executes the actions we for the given commands and updates logic variables for other areas of the code.
void executeCommands() {
    if (Serial.available()) {
        // All messages between nano and uno are separated by '\n'. Nano just sends integers.
        // The return is used (instead of break) when 'lastSessionLatestUpdateTime' shouldn't be updated.
        switch (Serial.readStringUntil('\n').toInt()) {
        case OPEN_DOOR:
            // A hand or Tag was accepted, so it gives it's feedback
            inputAccepted();
            rgbled.setColor(DOOR_OPEN_COLOR);
            delay(250);
            servo.rotate(190, 1500);

            // Set the time for session to close to 'DOOR_OPEN_TIME' and block other actions
            lastSessionLatestUpdateTime = millis() - (MINIMUM_TIME_BETWEEN_SESSIONS - DOOR_OPEN_TIME);
            closing = true;
            return;
        case SOUND_ALARM:
            buzzer.buzz(ALARM_BUZZ_SOUND, ALARM_TIME);
            rgbled.setColorBlink(ALARM_COLOR, ALARM_TIME, ALARM);
            servo.rotate(-190, 1500);

            // Set the time for session to close to 'ALARM_TIME' and block other actions
            lastSessionLatestUpdateTime = millis() - (MINIMUM_TIME_BETWEEN_SESSIONS - ALARM_TIME);
            closing = true;
            return;
        case WARN_INVALID_NFC_TAG:
            inputDenied();
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            // Allow tag to be read again
            blockTagReader(false);
            break;
        case WARN_INVALID_HAND_CODE:
            inputDenied();
            // Wait for Node-red
            rgbled.setColorBlink(THINKING_COLOR, 0, THINKING);
            break;
        case REQUEST_HAND_PHOTO_UPLOAD:
            // If this is run after an nfc, the user will received the feedback that the tag was accepted.
            if (lastAction == NFC) { inputAccepted(); }
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            // Delay to let user prepare for hand shot
            delay(HAND_WAIT_INPUT_TIME - 500);
            lastAction = UPLOAD_HAND_PHOTO;
            Serial.println(UPLOAD_HAND_PHOTO);
            // The script is delayed half a second to make sure the camera takes the picture when the light is in "wait for user input mode"
            // In other words, this delay attemps to coincide the change to "thinking" color with the photo shot
            delay(500);
            rgbled.setColorBlink(THINKING_COLOR, 0, THINKING);
            break;
        default:
            return;
        }
        lastSessionLatestUpdateTime = currentTime;
    }
}


// Updates camera light according to light sensed. If humanPresent set to off, it turns off the camera light.
void updateCameraLight(bool humanPresent = true) {
    static bool isCameraLightOn = false;
    if ((!humanPresent || lightSensor.readLightPercentage() > CAMERA_LIGHT_ACTIVATION_THRESHOLD) && isCameraLightOn) {
        Serial.println(TURN_OFF_LIGHT);
        isCameraLightOn = false;
    }
    else if (humanPresent && lightSensor.readLightPercentage() <= CAMERA_LIGHT_ACTIVATION_THRESHOLD && !isCameraLightOn) {
        Serial.println(TURN_ON_LIGHT);
        isCameraLightOn = true;
    }

}

void checkDetection() {

    // Checks for human and if detected and aren't in the process of closing session updates the session timer
    if (humanSensor.detectHuman() && !closing) {
        lastSessionLatestUpdateTime = currentTime;
        // Before the session starts, this is run once so that the tag can be read (only when a tag is read a session really starts)
        if (!humanNearby) {
            humanNearby = true;
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            blockTagReader(false);
        }
    }
    else if (currentTime - lastSessionLatestUpdateTime > MINIMUM_TIME_BETWEEN_SESSIONS && humanNearby) {
        // When 'currentTime' and 'lastSessionLatestUpdateTime' diference is big enough:
        // This piece of code sets everything to default, when a session ends/a long time has passed since a user got near.
        // After, Arduino will reset to initial behavior (waiting for human to get nearby)
        updateCameraLight(false);
        servo.write(-190);
        rgbled.setColor(OFF);
        humanNearby = false;
        sessionOpen = false;
        closing = false;
        delay(5000);
    }
}

void setup() {
    delay(5000);
    Serial.begin(9600);
    // This timeout makes sure the thread doesn't stay too long waiting for messages. Which allows sensors updates to get updated faster.
    Serial.setTimeout(100);
    Serial.println(TURN_OFF_LIGHT); // camera led gets turned off when system reboots.
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Buzzer, Light Sensor and LED - Started");
    Serial.println("Arduino Uno - Started Setup");
    Serial.println("Conecting to Nano 33 IoT...");
    while (true) {
        if (Serial.available())
            if (Serial.readStringUntil('\n').toInt() == PING)
                break;
    }
    Serial.println("Conected to Nano 33 IoT");
    Serial.println("NFC Adapter - Starting...");
    nfc.begin(true);
    Serial.println("NFC Adapter - Started");
    humanSensor.begin();
    servo.begin();
    Serial.println("Arduino Uno - Finished Setup");
    delay(3000);
}


void loop() {
    // The more frequent update functions are called, the better they work. Explained in more detail in functions definitions
    rgbled.update();
    servo.update();
    currentTime = millis();
    checkDetection();

    // Inside the if is the main code that allows to system to operate.
    // If a human gets nearby it is run.
    // It stops if door is open, alarm gets activated or human goes away
    if (humanNearby && !closing) {
        updateCameraLight();
        executeCommands();
        checkTag();
    }

    digitalWrite(LED_BUILTIN, isBuiltInLedOn ? LOW : HIGH);
    isBuiltInLedOn = !isBuiltInLedOn;
    delay(DEFAULT_MINIMUM_DELAY_TIME);
}