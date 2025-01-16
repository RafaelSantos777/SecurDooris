#include "HumanSensor.h"

/**
 * @file HumanSensor.cpp
 * @brief Implementation of the HumanSensor class for detecting human presence.
 *
 * This file contains the implementation of the HumanSensor class,
 * which provides methods to initialize and detect human presence using a sensor.
 */

 /**
  * @brief Constructor for the HumanSensor class.
  * @param sensitivity The sensitivity of the sensor.
  * @param detectInterval The interval between detection checks.
  */
HumanSensor::HumanSensor(float sensitivity, int detectInterval) :PresenceDetector(movementSensor, sensitivity, 10.0, detectInterval) {}

/**
 * @brief Initializes the human presence sensor.
 *
 * This method must be called in the setup function for the sensor to work.
 */
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

/**
 * @brief Detects human presence.
 * @param minimumSensorsDetect The minimum number of sensors that need to detect presence.
 * @return True if human presence is detected, false otherwise.
 */
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
