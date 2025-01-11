#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>
// #include <InternetCommunication.h>
// #include <BoardCommands.h>


const int DEFAULT_MINIMUM_DELAY_TIME = 50;
Buzzer buzzer(2);
LightSensor lightSensor(A0); // 5V
RGBLED rgbled(4, 5, 6); // R, G(far gnd), B(side G)
HumanSensor humanSensor; // 3.3V or 5V
NfcAdapter nfc(pn532_i2c); // 3.3V or 5V
SecurDoorisServo servo(8); // 5V
// SecurDoorisMQTTClient mqttClient;

// const char* MQTT_BROKER = "?????"; // TODO

// TODO TEMPORARY CODE
unsigned long blockEndTime = 0;

void blockReadings(unsigned long duration) {
    blockEndTime = millis() + duration;
}

bool areReadingsBlocked() {
    return millis() < blockEndTime;
}
// TEMPORARY CODE

// void updateCameraLight() {
//     static bool isCameraLightOn = false;
//     static const int CAMERA_LIGHT_ACTIVATION_THRESHOLD = 40;
//     if (lightSensor.readLightPercentage() <= CAMERA_LIGHT_ACTIVATION_THRESHOLD && !isCameraLightOn) {
//         Serial1.write(TURN_ON_LIGHT);
//         isCameraLightOn = false;
//     }
//     else if (lightSensor.readLightPercentage() > CAMERA_LIGHT_ACTIVATION_THRESHOLD && isCameraLightOn) {
//         Serial1.write(TURN_OFF_LIGHT);
//         isCameraLightOn = true;
//     }
// }

void setup() {
    delay(3000);
    Serial.begin(115200);
    Serial.println("Arduino Nano 33 IoT - Started");
    // connectToWiFi();
    // mqttClient.connect(MQTT_BROKER);
    humanSensor.begin();
    nfc.begin(false);
    servo.begin();
}

void loop() {
    Serial.print("->L");
    rgbled.update();
    servo.update();
    // updateCameraLight();
    // mqttClient.poll();
    if (areReadingsBlocked() || !nfc.tagPresent()) {
        Serial.print("!");
        delay(DEFAULT_MINIMUM_DELAY_TIME);
        return;
    }
    blockReadings(7000);
    Serial.print("T");
    String nfcTagId = nfc.read().getUidString();
    Serial.println("NFC Tag ID: " + nfcTagId);
    Serial.print("H");
    if (humanSensor.detectHuman())
        Serial.println("Sensor found human");
    else
        Serial.println("found nothing");
    Serial.print("D");
    Serial.println(lightSensor.readLightPercentage());
    Serial.print("S");
    buzzer.buzz(3000, 5000);
    Serial.print("F");
    rgbled.setColor(GREEN, 5000);
    Serial.print("M");
    servo.rotate(90, 1500);
    Serial.print("|");
    delay(DEFAULT_MINIMUM_DELAY_TIME);
}
