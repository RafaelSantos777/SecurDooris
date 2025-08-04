#include <LightSensor.h>
#include <Arduino.h>
/**
 * @file LightSensor.cpp
 * @brief Implementation of the LightSensor class for reading light levels.
 *
 * This file contains the implementation of the LightSensor class,
 * which provides methods to read light levels with the light sensor.
 */

 /**
  * @brief Constructor for the LightSensor class.
  * @param pin The pin number to which the light sensor is connected.
  */
LightSensor::LightSensor(int pin) : pin(pin) {
}

/**
 * @brief Reads the light level as a percentage.
 * @return The light level as a percentage (0-100).
 */
int LightSensor::readLightPercentage() {
    int analogLight = analogRead(pin);
    return map(analogLight, 0, MAX_ANALOG_LIGHT, 0, 100);
}
