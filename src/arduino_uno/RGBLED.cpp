#include <Arduino.h>
#include <RGBLED.h>
#include <math.h>

/**
 * @brief Constructor for RGBLED class.
 * @param redPin Pin number for the red LED.
 * @param greenPin Pin number for the green LED.
 * @param bluePin Pin number for the blue LED.
 */
RGBLED::RGBLED(int redPin, int greenPin, int bluePin) : redPin(redPin), greenPin(greenPin), bluePin(bluePin) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

/**
 * @brief Sets the color of the RGB LED.
 * @param color Color to set.
 */
void RGBLED::set(Color color) {
    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);
}

/**
 * @brief Sets the color of the RGB LED.
 * @param color Color to set.
 * @param duration Duration to keep the color. (0 equals Infinite)
 */
void RGBLED::setColor(Color color, unsigned long duration) {//maybe merge with bellow
    set(color);
    endTime = duration == 0 ? 0 : millis() + duration;
    Serial.println("blink reset");
    loopTime = 0;
}

/**
 * @brief Sets the RGB LED to blink with a specified color.
 * @param color Color to set.
 * @param duration Duration to keep the color. (0 equals Infinite)
 * @param blinkDuration Duration of each blink.
 * @param fade Indicates if the blink should fade. (use with high durations, >500)
 */
void RGBLED::setColorBlink(Color color, unsigned long duration, long blinkDuration, bool fade) {
    Serial.println("blink");
    set(color);
    endTime = duration == 0 ? 0 : millis() + duration;
    on = true;
    currentColor = color;
    setTime = millis();
    loopTime = blinkDuration;
    fadeBlink = fade;
}

/**
 * @brief Updates the RGB LED state.
 */
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