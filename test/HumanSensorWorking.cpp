#include <Arduino.h>
#include <HumanSensor.h>
#include <Wire.h>

HumanSensor humanSensor;

void setup() {
    Serial.begin(115200);
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
