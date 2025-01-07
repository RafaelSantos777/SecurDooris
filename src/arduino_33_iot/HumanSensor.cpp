#include "HumanSensor.h"
#include "Grove_Human_Presence_Sensor.h"

HumanSensor::HumanSensor(float sensitiviy, int detect_interval) :PresenceDetector(movementSensor, sensitiviy, 10.0, detect_interval)
{
    last_time = millis();
}

bool HumanSensor::humanDetected(int minimum_sensors_detect)
{
    loop();
    uint32_t now = millis();
    int detected = 0;
    if (now - last_time > 100) {
        if (presentFullField(false)) {
            detected += presentField1() ? 1 : 0;
            detected += presentField2() ? 1 : 0;
            detected += presentField3() ? 1 : 0;
            detected += presentField4() ? 1 : 0;
        }
        last_time = now;
    }
    return detected >= minimum_sensors_detect;
}

// mandatory to be in setup for human sensor to work
void HumanSensor::beginAndWire()
{
    Wire.begin();
    Serial.println("Starting - Human Presence Sensor");
    if (movementSensor.initialize() == false) {
        Serial.println("Human Presence Sensor not found. Check wiring.");
        while (1);
    }
    Serial.println("Started - Human Presence Sensor");
}
