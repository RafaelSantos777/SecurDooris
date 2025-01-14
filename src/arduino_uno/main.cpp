#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <BoardCommands.h>


const long MINIMUM_TIME_BETWEEN_SESSIONS = 1L * 60 * 1000;
const int DOOR_OPEN_TIME = 15000;
const int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 20;
const int DEFAULT_MINIMUM_DELAY_TIME = 50;
const int FAST_FEEDBACK_TIME = 1000;
const int HAND_WAIT_INPUT_TIME = 2000;
const int ALARM_TIME = 10000;

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


// TODO TEMPORARY CODE
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
            lastSessionLatestUpdateTime = currentTime;
            Serial.println("Session open");
            sessionOpen = true;
            Serial.println(UPDATE_SESSION);
        }
        else Serial.println("Session Already open");
        Serial.println(NFC);
        Serial.println(nfc.read().getUidString());
        lastSessionLatestUpdateTime = currentTime;
        rgbled.setColor(THINKING_COLOR);
        lastAction = NFC;
    }
}

void executeCommands() {
    if (Serial.available()) {
        int input = Serial.readStringUntil('\n').toInt();
        Serial.println("Received: " + String(input));
        switch (input) {
        case OPEN_DOOR:
            rgbled.setColor(INPUT_ACCEPTED_COLOR);
            delay(FAST_FEEDBACK_TIME);
            rgbled.setColor(DOOR_OPEN_COLOR);
            delay(250);
            servo.rotate(190, 1500);
            lastSessionLatestUpdateTime = millis() - (MINIMUM_TIME_BETWEEN_SESSIONS - DOOR_OPEN_TIME);
            closing = true;
            return;
        case SOUND_ALARM:
            buzzer.buzz(3000, ALARM_TIME);
            rgbled.setColor(ALARM_COLOR, ALARM_TIME, ALARM); //TODO blinking
            lastSessionLatestUpdateTime = -MINIMUM_TIME_BETWEEN_SESSIONS;
            servo.rotate(-190, 1500);
            closing = true;
            delay(ALARM_TIME);
            return;
        case WARN_INVALID_NFC_TAG:
            rgbled.setColor(INPUT_DENIED_COLOR);
            delay(FAST_FEEDBACK_TIME);
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            blockTagReader(false);
            break;
        case WARN_INVALID_HAND_CODE:
            rgbled.setColor(INPUT_DENIED_COLOR);
            delay(FAST_FEEDBACK_TIME);
            rgbled.setColor(THINKING_COLOR);
            break;
        case REQUEST_HAND_PHOTO_UPLOAD:
            if (lastAction == NFC)
            {
                rgbled.setColor(INPUT_ACCEPTED_COLOR);
                delay(FAST_FEEDBACK_TIME);
            }
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR, HAND_WAIT_INPUT_TIME);
            delay(HAND_WAIT_INPUT_TIME - 500);
            lastAction = UPLOAD_HAND_PHOTO;
            Serial.println(UPLOAD_HAND_PHOTO);
            delay(500);
            rgbled.setColor(THINKING_COLOR);
            break;
        default:
            break;
        }
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
        lastSessionLatestUpdateTime = currentTime;
        if (!humanNearby) {
            Serial.println("human nearby");
            humanNearby = true;
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            blockTagReader(false);
        }
    }
    else if (currentTime - lastSessionLatestUpdateTime > MINIMUM_TIME_BETWEEN_SESSIONS && humanNearby) {
        updateCameraLight(false);
        servo.rotate(-190, 1500);
        rgbled.setColor(OFF, 5000);
        Serial.println("human away");
        humanNearby = false;
        Serial.println("session closed");
        sessionOpen = false;
        closing = false;
    }
}

void setup() {
    delay(5000);
    Serial.begin(9600);
    Serial.setTimeout(100);
    Serial.println(TURN_OFF_LIGHT);
    Serial.println("Buzzer, Light Sensor and LED - Started");
    Serial.println("Arduino Uno - Started Setup");
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
    if (humanNearby) {
        updateCameraLight();
        executeCommands();
        checkTag();
    }
    delay(DEFAULT_MINIMUM_DELAY_TIME);
}