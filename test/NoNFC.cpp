#include <Arduino.h>
#include <Buzzer.h>
#include <LightSensor.h>
#include <RGBLED.h>
#include <HumanSensor.h>
#include <SecurDoorisServo.h>

Buzzer buzzer(2); // Change pin numbers
LightSensor lightSensor(A0);
RGBLED rgbled(4, 5, 6);
HumanSensor humanSensor;
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
    delay(3000);
    Serial.begin(115200);
    Serial.println("Arduino Nano 33 IoT - Started");
    servo.begin();
    humanSensor.begin(); // mandatory for human sensor to work
}

void loop() {
    rgbled.update();
    servo.update();
    if (areReadingsBlocked())
        return;
    blockReadings(7000);
    if (humanSensor.detectHuman())
    {
        Serial.println("Sensor found human");
    }
    else {
        Serial.println("found nothing");
    }
    Serial.println("Lightness %: " + (String)lightSensor.readLightPercentage());
    buzzer.buzz(1000, 5000);
    rgbled.setColor(GREEN, 5000);
    servo.rotate(90, 1500);
    delay(10);
}
