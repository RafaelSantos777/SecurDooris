#include <Arduino.h>
#include "Grove_Human_Presence_Sensor.h"

class HumanSensor : public PresenceDetector {

public:
    HumanSensor(float sensitivity = DEFAULT_PRESENCE_SENSITIVITY, int detect_interval = DEFAULT_DETECT_INTERVAL);
    void begin();
    bool detectHuman(int minimum_sensors_detect = DEFAULT_MINIMUM_SENSORS_DETECT);

private:
    static const float DEFAULT_PRESENCE_SENSITIVITY = 5.0;
    static const int DEFAULT_DETECT_INTERVAL = 50;
    static const int DEFAULT_MINIMUM_SENSORS_DETECT = 2;
    AK9753 movementSensor;
    unsigned long lastTime;
};
