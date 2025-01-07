#include "HumanSensor.h"

HumanSensor::HumanSensor(float sensitivity, int detectInterval) :PresenceDetector(movementSensor, sensitivity, 10.0, detectInterval) {
}

// mandatory to be in setup for human sensor to work
void HumanSensor::begin() {
    Serial.println("Human Presence Sensor - Starting...");
    Wire.begin();
    if (!movementSensor.initialize()) {
        Serial.println("Human Presence Sensor not found. Check wiring.");
        while (true);
    }
    lastTime = millis();
    Serial.println("Human Presence Sensor - Done");

}

bool HumanSensor::detectHuman(int minimumSensorsDetect) {
    loop();
    unsigned long now = millis();
    int detected = 0;
    if (now - lastTime > 100) {
        if (presentFullField(false)) {
            detected += presentField1() ? 1 : 0;
            detected += presentField2() ? 1 : 0;
            detected += presentField3() ? 1 : 0;
            detected += presentField4() ? 1 : 0;
        }
        lastTime = now;
    }
    return detected >= minimumSensorsDetect;
}

