#include <LightSensor.h>

LightSensor::LightSensor(int pin) : pin(pin) {
}

int LightSensor::readLightPercentage() {
    int analogLight = analogRead(pin);
    return map(analogLight, 0, MAX_ANALOG_LIGHT, 0, 100);
}
