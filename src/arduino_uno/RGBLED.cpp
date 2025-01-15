#include <Arduino.h>
#include <RGBLED.h>
#include <math.h>

RGBLED::RGBLED(int redPin, int greenPin, int bluePin) : redPin(redPin), greenPin(greenPin), bluePin(bluePin) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBLED::set(Color color) {

    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);
}

void RGBLED::setColor(Color color, unsigned long duration) {//maybe merge with bellow
    set(color);
    endTime = duration == 0 ? 0 : millis() + duration;
}



void RGBLED::setColorBlink(Color color, unsigned long duration, long blinkDuration, bool fade) {
    set(color);
    endTime = duration == 0 ? 0 : millis() + duration;
    on = true;
    currentColor = color;
    setTime = millis();
    loopTime = blinkDuration;
    fadeBlink = fade;
}

void RGBLED::update() {
    if (endTime > 0 && millis() > endTime) {
        set(OFF);
        endTime = 0;
        loopTime = 0;
    }
    if (loopTime > 0) {

        if (fadeBlink) {
            float factor = (cos(((millis() - setTime) * PI) / loopTime) + 1) / 2;
            set({ (int)(currentColor.red * factor),  (int)(currentColor.green * factor),  (int)(currentColor.blue * factor) });
        }
        else
            if ((int)((millis() - setTime) / loopTime) % 2 == 0) {
                if (!on) {
                    set(currentColor);
                    on = true;
                }
            }
            else
                if (on) {
                    set(OFF);
                    on = false;
                }
    }
}