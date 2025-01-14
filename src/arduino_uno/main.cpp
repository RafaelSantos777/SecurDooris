#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <BoardCommands.h>

const int MINIMUM_TIME_BETWEEN_SESSIONS = 60 * 1000;
const int MAXIMUM_WAIT_FOR_HUMAN_PRESENCE = 10 * 1000;
const int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 20;
const int DEFAULT_MINIMUM_DELAY_TIME = 50;
const int FAST_FEEDBACK_TIME = 2000;
const int HAND_WAIT_INPUT_TIME = 2000;

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
unsigned long currentTime = 0;
unsigned long lastHumanDetectionTime = 0;
unsigned long lastSessionLatestUpdateTime = 0;
bool humanNearby = false;
int lastAction = 0;


void readAndSendTag() {
    blockReadings();
    Serial.println(NFC);
    Serial.println(nfc.read().getUidString());
    rgbled.setColor(THINKING_COLOR);
    lastAction = NFC;
}

void executeCommands() {
    if (Serial.available()) {
        int input = Serial.readStringUntil('\n').toInt();
        Serial.println("Received: " + String(input));
        switch (input) {
        case OPEN_DOOR:
            rgbled.setColor(INPUT_ACCEPTED_COLOR);
            delay(FAST_FEEDBACK_TIME);
            Serial.println("Opening door");
            rgbled.setColor(DOOR_OPEN_COLOR);
            delay(FAST_FEEDBACK_TIME);
            servo.rotate(190, 1500);
            break;
        case SOUND_ALARM:
            Serial.println("Sounding alarm");
            buzzer.buzz(3000, 5000);
            rgbled.setColor(ALARM_COLOR, 5000, ALARM); //TODO blinking
            break;
        case WARN_INVALID_NFC_TAG:
            rgbled.setColor(INPUT_DENIED_COLOR);
            delay(FAST_FEEDBACK_TIME);
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
            blockReadings(0);
            break;
        case WARN_INVALID_HAND_CODE:
            rgbled.setColor(INPUT_DENIED_COLOR);
            break;
        case REQUEST_HAND_PHOTO_UPLOAD:
            if (lastAction == NFC)
            {
                rgbled.setColor(INPUT_ACCEPTED_COLOR);
                delay(FAST_FEEDBACK_TIME);
            }
            Serial.println("Requesting hand number");
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

void detectionLogic() {
    if (humanSensor.detectHuman()) { //TODO não estar sempre
        lastHumanDetectionTime = millis();
        lastSessionLatestUpdateTime = millis();
        if (!humanNearby) {
            humanNearby = true;
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR);
        }
    }
    else {
        if (currentTime - lastHumanDetectionTime > MAXIMUM_WAIT_FOR_HUMAN_PRESENCE && humanNearby) {
            updateCameraLight(false);
            servo.rotate(-190, 1500);
            rgbled.setColor(OFF, 5000);
            humanNearby = false;
        }
    }
}

void setup() {
    delay(5000);
    Serial.begin(9600);
    Serial.setTimeout(100);
    Serial.println(TURN_OFF_LIGHT);
    Serial.println("Buzzer, Light Sensor and LED - Started");
    Serial.println("Arduino Uno - Started Setup");
    humanSensor.begin();
    Serial.println("NFC Adapter - Starting...");
    nfc.begin(false);
    Serial.println("NFC Adapter - Started");
    servo.begin();
    Serial.println("Arduino Uno - Finished Setup");
    delay(3000);
}


void loop() {
    rgbled.update();
    servo.update();
    currentTime = millis();
    detectionLogic();
    if (humanNearby) {
        updateCameraLight();
        executeCommands();
        if (readingsBlocked() || !nfc.tagPresent(12.5)) {
            return;
        }
        else {
            if (currentTime - lastSessionLatestUpdateTime > MINIMUM_TIME_BETWEEN_SESSIONS) {
                lastSessionLatestUpdateTime = currentTime;
                Serial.println("Update Session message");
                Serial.println(UPDATE_SESSION);
            }
            readAndSendTag();
        }
    }

    delay(DEFAULT_MINIMUM_DELAY_TIME);
}