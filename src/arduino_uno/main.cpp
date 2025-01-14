#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <BoardCommands.h>

const int MINIMUM_TIME_BETWEEN_SESSIONS = 60000;
const int MAXIMUM_WAIT_FOR_HUMAN_PRESENCE = 10000;
const int DEFAULT_MINIMUM_DELAY_TIME = 50;
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
unsigned long blockEndTime = 0;
unsigned long currentTime = 0;
unsigned long lastHumanDetectionTime = 0;
unsigned long lastSessionLatestUpdateTime = 0;
bool humanNearby = false;

void blockReadings(unsigned long duration) {
    blockEndTime = currentTime + duration;
}

bool areReadingsBlocked() {
    return currentTime < blockEndTime;
}
// TEMPORARY CODE END



void readAndSendTag() {
    blockReadings(7000);
    Serial.print(String(NFC) + nfc.read().getUidString());
    rgbled.setColor(THINKING_COLOR);
}

void executeCommands() {
    if (Serial.available()) {
        switch (Serial.read()) {
        case OPEN_DOOR:
            servo.rotate(180, 1500);
            rgbled.setColor(DOOR_OPEN_COLOR);
            break;
        case SOUND_ALARM:
            buzzer.buzz(3000, 5000);
            rgbled.setColor(ALARM_COLOR, 5000, ALARM); //TODO blinking
            break;
        case WARN_INVALID_NFC_TAG:
            rgbled.setColor(INPUT_DENIED_COLOR, 2000);
            break;
        case WARN_INVALID_HAND_CODE:
            rgbled.setColor(INPUT_DENIED_COLOR, 2000);
            break;
        case REQUEST_HAND_PHOTO_UPLOAD:
            rgbled.setColor(INPUT_ACCEPTED_COLOR);
            delay(1000);
            rgbled.setColor(WAIT_FOR_USER_INPUT_COLOR, 2000);
            delay(1500);
            if (IN_UNO_DEBUG_MODE)
                Serial.print(UPLOAD_HAND_PHOTO);
            else
                Serial.write(UPLOAD_HAND_PHOTO);
            delay(500);
            rgbled.setColor(THINKING_COLOR);
            break;
        }
    }
}

void updateCameraLight(bool humanPresent = true) {
    static bool isCameraLightOn = false;
    static const int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 10;
    if ((!humanPresent || lightSensor.readLightPercentage() > CAMERA_LIGHT_ACTIVATION_THRESHOLD) && isCameraLightOn) {
        if (IN_UNO_DEBUG_MODE)
            Serial.print(TURN_OFF_LIGHT);
        else
            Serial.write(TURN_OFF_LIGHT);
        isCameraLightOn = false;
    }
    else if (lightSensor.readLightPercentage() <= CAMERA_LIGHT_ACTIVATION_THRESHOLD && !isCameraLightOn) {
        if (IN_UNO_DEBUG_MODE)
            Serial.print(TURN_ON_LIGHT);
        else
            Serial.write(TURN_ON_LIGHT);
        isCameraLightOn = true;
    }

}

void detectionLogic() {
    if (humanSensor.detectHuman()) {
        updateCameraLight();
        lastHumanDetectionTime = millis();
        lastSessionLatestUpdateTime = millis();
        if (!humanNearby) humanNearby = true;
    }
    else {
        if (currentTime - lastHumanDetectionTime > MAXIMUM_WAIT_FOR_HUMAN_PRESENCE) {
            updateCameraLight(false);
            servo.rotate(-180, 1500);
            rgbled.setColor(OFF, 5000);
            humanNearby = false;
        }
    }
}

void setup() {
    delay(5000);
    Serial.begin(9600);
    if (IN_UNO_DEBUG_MODE)
        Serial.print(TURN_OFF_LIGHT);
    else
        Serial.write(TURN_OFF_LIGHT);
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
        if (areReadingsBlocked() || !nfc.tagPresent()) {
            delay(DEFAULT_MINIMUM_DELAY_TIME);
            return;
        }
        else {
            if (currentTime - lastSessionLatestUpdateTime > MINIMUM_TIME_BETWEEN_SESSIONS) {
                lastSessionLatestUpdateTime = currentTime;
                if (IN_UNO_DEBUG_MODE)
                    Serial.print(UPDATE_SESSION);
                else
                    Serial.write(UPDATE_SESSION);
            }
            readAndSendTag();
        }

        executeCommands();
    }

    delay(DEFAULT_MINIMUM_DELAY_TIME);
}