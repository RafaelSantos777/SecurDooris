#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <SecurDoorisServo.h>

Buzzer buzzer(2); // Change pin numbers
LightSensor lightSensor(A0);
RGBLED rgbled(4, 5, 6);
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
    delay(5000);
    Serial.begin(115200);
}

void loop() {
    rgbled.update();
    servo.update();
    if (areReadingsBlocked())
        return;
    blockReadings(7000);
    Serial.println("Lightness %: " + (String)lightSensor.getLightPercentage());
    buzzer.buzz(1000, 5000);
    rgbled.setColor(GREEN, 5000);
    servo.rotate(90, 1500);
    delay(10);
}
