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

bool ledOn = false;

long currentTime = 0;
long lastSessionLatestUpdateTime = -MINIMUM_TIME_BETWEEN_SESSIONS;
bool sessionOpen = false;
bool humanNearby = false;
bool closing = false;
int lastAction = 0;

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
        Serial.println("updating sessiontimer - nfc read");
        lastSessionLatestUpdateTime = currentTime;
        rgbled.setColorBlink(THINKING_COLOR, 0, THINKING);
        lastAction = NFC;
    }
}

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

void executeCommands() {
    if (Serial.available()) {
        switch (Serial.readStringUntil('\n').toInt()) {
        case OPEN_DOOR:
            inputAccepted();
            rgbled.setColor(DOOR_OPEN_COLOR);
            delay(250);
            servo.rotate(190, 1500);
            Serial.println("updating sessiontimer - open door");
            lastSessionLatestUpdateTime = millis() - (MINIMUM_TIME_BETWEEN_SESSIONS - DOOR_OPEN_TIME);
            closing = true;
            return;
        case SOUND_ALARM:
            buzzer.buzz(ALARM_BUZZ_SOUND, ALARM_TIME);
            rgbled.setColorBlink(ALARM_COLOR, ALARM_TIME, ALARM);
            Serial.println("updating sessiontimer - alarm");
            lastSessionLatestUpdateTime = millis() - (MINIMUM_TIME_BETWEEN_SESSIONS - ALARM_TIME);
            servo.rotate(-190, 1500);
            closing = true;
            return;
        case WARN_INVALID_NFC_TAG:
            inputDenied();
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            blockTagReader(false);
            break;
        case WARN_INVALID_HAND_CODE:
            inputDenied();
            rgbled.setColorBlink(THINKING_COLOR, 0, THINKING);
            break;
        case REQUEST_HAND_PHOTO_UPLOAD:
            if (lastAction == NFC) { inputAccepted(); }
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            delay(HAND_WAIT_INPUT_TIME - 500);
            lastAction = UPLOAD_HAND_PHOTO;
            Serial.println(UPLOAD_HAND_PHOTO);
            delay(500);
            rgbled.setColorBlink(THINKING_COLOR, 0, THINKING);
            break;
        default:
            return;
        }
        Serial.println("updating sessiontimer - command");
        lastSessionLatestUpdateTime = currentTime;
    }
}

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
    if (humanSensor.detectHuman() && !closing) { //TODO não estar sempre
        Serial.println("updating sessiontimer - human detection");
        lastSessionLatestUpdateTime = currentTime;
        if (!humanNearby) {
            humanNearby = true;
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            blockTagReader(false);
        }
    }
    else if (currentTime - lastSessionLatestUpdateTime > MINIMUM_TIME_BETWEEN_SESSIONS && humanNearby) {
        Serial.println("Closing everything");
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
    Serial.setTimeout(100);
    Serial.println(TURN_OFF_LIGHT);
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
    rgbled.update();
    servo.update();
    currentTime = millis();
    checkDetection();
    if (humanNearby && !closing) {
        updateCameraLight();
        executeCommands();
        checkTag();
    }

    digitalWrite(LED_BUILTIN, ledOn ? LOW : HIGH);
    ledOn = !ledOn;
    delay(DEFAULT_MINIMUM_DELAY_TIME);
}