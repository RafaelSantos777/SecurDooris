#include <Arduino.h>

class LightSensor {

public:
    LightSensor(int pin);
    int readLightPercentage();

private:
    static const int MAX_ANALOG_LIGHT = 1023;
    const int pin;
};
