#include "Grove_Human_Presence_Sensor.h"
/**
 * @file HumanSensor.h
 * @brief Defines the HumanSensor class for detecting human presence.
 * This file contains the definition of the HumanSensor class,
 * which extends the PresenceDetector class to provide methods for detecting
 * human presence using the Grove Human Presence Sensor.
 */

 /**
  * @class HumanSensor
  * @brief A class to detect human presence using the Grove Human Presence Sensor.
  */
class HumanSensor : public PresenceDetector {

public:
    /**
         * @brief Constructs a HumanSensor object.
         * @param sensitivity The sensitivity for detecting presence (default is 5.0).
         * @param detect_interval The interval for detection in milliseconds (default is 50).
         */
    HumanSensor(float sensitivity = DEFAULT_PRESENCE_SENSITIVITY, int detect_interval = DEFAULT_DETECT_INTERVAL);

    /**
     * @brief Initializes the human sensor.
     */
    void begin();

    /**
     * @brief Detects human presence.
     * @param minimum_sensors_detect The minimum number of sensors that need to detect presence (default is 2).
     * @return True if human presence is detected, false otherwise.
     */
    bool detectHuman(int minimum_sensors_detect = DEFAULT_MINIMUM_SENSORS_DETECT);

private:
    static constexpr float DEFAULT_PRESENCE_SENSITIVITY = 5.0; ///< Default sensitivity for detecting presence.
    static constexpr int DEFAULT_DETECT_INTERVAL = 50;         ///< Default interval for detection in milliseconds.
    static constexpr int DEFAULT_MINIMUM_SENSORS_DETECT = 2;   ///< Default minimum number of sensors to detect presence.
    AK9753 movementSensor;                                     ///< The sensor used for detecting human presence.
    unsigned long lastTime;                                    ///< The last time a detection was made.
};
