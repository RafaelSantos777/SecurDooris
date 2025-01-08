#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <SoftwareSerial.h>
#include <BoardCommunicationCommands.h>

Buzzer buzzer(2); // Change pin numbers
LightSensor lightSensor(A0);
RGBLED rgbled(4, 5, 6);
HumanSensor humanSensor;
SecurDoorisNFCAdapter nfcAdapter;
SecurDoorisServo servo(8);
SoftwareSerial cameraSerial(10, 11); // RX, TX pins for SoftwareSerial

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
    static int isCameraLightOn = false;
    static int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 40;
    if (lightSensor.readLightPercentage() <= CAMERA_LIGHT_ACTIVATION_THRESHOLD && !isCameraLightOn) {
        cameraSerial.write(TURN_ON_LIGHT);
        isCameraLightOn = false;
    }
    else if (lightSensor.readLightPercentage() > CAMERA_LIGHT_ACTIVATION_THRESHOLD && isCameraLightOn) {
        cameraSerial.write(TURN_OFF_LIGHT);
        isCameraLightOn = true;
    }
}

void setup() {
    delay(7000);
    Serial.begin(115200);
    Serial.println("Arduino Nano 33 IoT - Started");
    cameraSerial.begin(115200);
    humanSensor.begin(); // mandatory for human sensor to work
}

void loop() {
    rgbled.update();
    servo.update();
    updateCameraLight();
    if (areReadingsBlocked() || !nfcAdapter.tagPresent())
        return;
    blockReadings(2000);
    if (humanSensor.detectHuman())
        Serial.println("Sensor found human");
    else
        Serial.println("found nothing");
    String nfcTagId = nfcAdapter.readTagId();
    Serial.println("NFC Tag ID: " + nfcTagId);
    buzzer.buzz(3000, 5000);
    rgbled.setColor(GREEN, 5000);
    servo.rotate(90, 1500);
    delay(10);
}
