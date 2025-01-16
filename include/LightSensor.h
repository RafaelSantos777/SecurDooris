/**
 * @file LightSensor.h
 * @brief Defines the LightSensor class for reading light levels.
 *
 * This file contains the definition of the LightSensor class,
 * which provides methods to read the light level as a thousanth
 * using an analog light sensor.
 */

 /**
  * @class LightSensor
  * @brief A class to read light levels using an analog light sensor.
  */
class LightSensor {

public:
    /**
         * @brief Constructs a LightSensor object.
         * @param pin The pin number where the light sensor is connected.
         */
    LightSensor(int pin);

    /**
     * @brief Reads the light level as a thousanth.
     * @return The light level as a thousanth (0-100).
     */
    int readLightPercentage();

private:
    static const int MAX_ANALOG_LIGHT = 1023;  ///< Maximum analog value for the light sensor.
    const int pin; ///< The pin number where the light sensor is connected.
};
