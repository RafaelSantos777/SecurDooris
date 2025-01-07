#include <Arduino.h>
#include <HumanSensor.h>
#include <Wire.h>

HumanSensor humanSensor;

void setup() {
    delay(7000);
    Serial.begin(115200);
    Serial.println("Arduino Nano 33 IoT - Started");
    humanSensor.begin(); // mandatory for human sensor to work

}

void loop() {
    if (humanSensor.detectHuman())
    {
        Serial.println("Sensor found human");
    }
    else {
        Serial.println("found nothing");
    }
    delay(1000);
}
