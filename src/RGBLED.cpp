#include <RGBLED.h>

RGBLED::RGBLED(int redPin, int greenPin, int bluePin) : redPin(redPin), greenPin(greenPin), bluePin(bluePin) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBLED::setColor(Color color, unsigned long duration) {
    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);
    endTime = duration == 0 ? 0 : millis() + duration;
}

void RGBLED::update() {
    if (endTime > 0 && millis() > endTime)
        setColor(OFF);
}
