#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <BoardCommands.h>


const int DEFAULT_MINIMUM_DELAY_TIME = 50;
Buzzer buzzer(2);
LightSensor lightSensor(A0); // 5V
RGBLED rgbled(3, 5, 6); // R G(far gnd) B(side G)
HumanSensor humanSensor; // 3.3V or 5V
NfcAdapter nfc(pn532_i2c); // 3.3V or 5V, SCL(A5), SDA(A4)
SecurDoorisServo servo(8); // 5V


// TODO TEMPORARY CODE
unsigned long blockEndTime = 0;

void blockReadings(unsigned long duration) {
    blockEndTime = millis() + duration;
}

bool areReadingsBlocked() {
    return millis() < blockEndTime;
}
// TEMPORARY CODE

void updateCameraLight() {
    static bool isCameraLightOn = false;
    static const int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 40;
    if (lightSensor.readLightPercentage() <= CAMERA_LIGHT_ACTIVATION_THRESHOLD && !isCameraLightOn) {
        Serial.print(TURN_ON_LIGHT);
        isCameraLightOn = true;
    }
    else if (lightSensor.readLightPercentage() > CAMERA_LIGHT_ACTIVATION_THRESHOLD && isCameraLightOn) {
        Serial.print(TURN_OFF_LIGHT);
        isCameraLightOn = false;
    }
}

void setup() {
    delay(3000);
    Serial.begin(9600);
    Serial.println("Buzzer, Light Sensor and LED - Started");
    Serial.println("Arduino Uno - Started Setup");
    humanSensor.begin();
    Serial.println("NFC Adapter - Starting...");
    nfc.begin(false);
    Serial.println("NFC Adapter - Started");
    servo.begin();
    Serial.println("Arduino Uno - Finished Setup");
    delay(DEFAULT_MINIMUM_DELAY_TIME);
}

void loop() {
    if (Serial.available()) {
        Serial.print("echo: " + Serial.readString());
    }
    rgbled.update();
    servo.update();
    updateCameraLight();
    if (areReadingsBlocked() || !nfc.tagPresent()) {
        delay(DEFAULT_MINIMUM_DELAY_TIME);
        return;
    }
    blockReadings(7000);
    String nfcTagId = nfc.read().getUidString();
    Serial.println("NFC Tag ID: " + nfcTagId);
    if (humanSensor.detectHuman())
        Serial.println("Sensor found human");
    else
        Serial.println("found nothing");
    buzzer.buzz(3000, 5000);
    rgbled.setColor(GREEN, 5000);
    servo.rotate(90, 1500);
    delay(DEFAULT_MINIMUM_DELAY_TIME);
}