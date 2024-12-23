#include <Arduino.h>

class LightSensor {
private:
    const int MAX_ANALOG_LIGHT = 1023;
    const int pin;
public:
    LightSensor(int pin);
    int getLightPercentage();
};
