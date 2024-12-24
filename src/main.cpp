#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <SecurDorisNFCAdapter.h>
#include <SecurDorisServo.h>

Buzzer buzzer(2); // Change pin numbers
LightSensor lightSensor(A0);
RGBLED rgbled(4, 5, 6);
SecurDorisNFCAdapter nfcAdapter;
SecurDoorisServo servo(8);

// TEMPORARY CODE
unsigned long blockEndTime = 0;

void blockReadings(long duration) {
    blockEndTime = millis() + duration;
}

bool areReadingsBlocked() {
    return millis() < blockEndTime;
}
// TEMPORARY CODE

void setup(void) {
    Serial.begin(115200);
}

void loop() {
    rgbled.update();
    servo.update();
    if (areReadingsBlocked() || !nfcAdapter.tagPresent())
        return;
    blockReadings(2000);
    String nfcTagId = nfcAdapter.getTagId();
    Serial.println("NFC Tag ID: " + nfcTagId);
    Serial.println("Lightness %: " + lightSensor.getLightPercentage());
    buzzer.buzz(3000, 5000);
    rgbled.setColor(GREEN, 5000);
    servo.rotate(90, 1500);
    delay(10);
}
