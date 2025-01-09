#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
#include <Communication.h>

Buzzer buzzer(2);
LightSensor lightSensor(A0);
RGBLED rgbled(4, 5, 6);
HumanSensor humanSensor;
SecurDoorisNFCAdapter nfcAdapter;
SecurDoorisServo servo(8);

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
        sendMQTTMessage(TURN_ON_LIGHT, BOARD_COMMUNICATION_TOPIC);
        isCameraLightOn = false;
    }
    else if (lightSensor.readLightPercentage() > CAMERA_LIGHT_ACTIVATION_THRESHOLD && isCameraLightOn) {
        sendMQTTMessage(TURN_OFF_LIGHT, BOARD_COMMUNICATION_TOPIC);
        isCameraLightOn = true;
    }
}

void setup() {
    delay(7000);
    Serial.begin(9600);
    Serial.println("Arduino Nano 33 IoT - Started");
    connectToWiFi();
    connectToMQTTClient();
    humanSensor.begin();
}

void loop() {
    rgbled.update();
    servo.update();
    updateCameraLight();
    mqttClient.poll();
    if (areReadingsBlocked() || !nfcAdapter.tagPresent())
        return;
    blockReadings(7000);
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
