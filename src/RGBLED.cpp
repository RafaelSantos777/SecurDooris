#include <RGBLED.h>

RGBLED::RGBLED(int redPin, int greenPin, int bluePin) : redPin(redPin), greenPin(greenPin), bluePin(bluePin) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBLED::setColor(Color color) {
    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);
}

void RGBLED::setColor(Color color, long duration) {
    setColor(color);
    endTime = millis() + duration;
}

void RGBLED::update() {
    if (millis() > endTime)
        return;
    setColor(OFF);
    resetTimer();
}

void RGBLED::resetTimer() {
    endTime = 0;
}
