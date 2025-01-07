#include <Arduino.h>
#include "Grove_Human_Presence_Sensor.h"

static const int DEFAULT_PRESENCE_SENSITIVITY = 5.0;
static const int DEFAULT_DETECT_INTERVAL = 50;
static const int DEFAULT_MINIMUM_SENSORS_DETECT = 2;

class HumanSensor : public PresenceDetector {

public:

    HumanSensor(float sensitiviy = DEFAULT_PRESENCE_SENSITIVITY, int detect_interval = DEFAULT_DETECT_INTERVAL);
    bool humanDetected(int minimum_sensors_detect = DEFAULT_MINIMUM_SENSORS_DETECT);
    void beginAndWire();


private:
    AK9753 movementSensor;
    uint32_t last_time;
};