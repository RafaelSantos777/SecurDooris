#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisNFCAdapter.h>
#include <SecurDoorisServo.h>

Buzzer buzzer(2); // Change pin numbers
LightSensor lightSensor(A0);
RGBLED rgbled(4, 5, 6);
HumanSensor humanSensor;
SecurDoorisNFCAdapter nfcAdapter;
SecurDoorisServo servo(8);

// TEMPORARY CODE
unsigned long blockEndTime = 0;

void blockReadings(unsigned long duration) {
    blockEndTime = millis() + duration;
}

bool areReadingsBlocked() {
    return millis() < blockEndTime;
}
// TEMPORARY CODE

void setup() {
    Serial.begin(115200);
    humanSensor.beginAndWire(); // mandatory for human sensor to work
}

void loop() {
    rgbled.update();
    servo.update();
    if (areReadingsBlocked() || !nfcAdapter.tagPresent())
        return;
    blockReadings(2000);
    if (humanSensor.humanDetected())
    {
        Serial.println("Sensor found human");
    }
    else {
        Serial.println("found nothing");
    }
    String nfcTagId = nfcAdapter.readTagId();
    Serial.println("NFC Tag ID: " + nfcTagId);
    Serial.println("Lightness %: " + (String)lightSensor.readLightPercentage());
    buzzer.buzz(3000, 5000);
    rgbled.setColor(GREEN, 5000);
    servo.rotate(90, 1500);
    delay(10);
}
