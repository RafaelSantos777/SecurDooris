#include <Buzzer.h>
#include <Arduino.h>

/**
 * @file Buzzer.cpp
 * @brief Implementation of the Buzzer class for controlling a buzzer.
 *
 * This file contains the implementation of the Buzzer class,
 * which provides methods to control the buzzer.
 */

 /**
  * @brief Constructor for the Buzzer class.
  * @param pin The pin number to which the buzzer is connected.
  */
Buzzer::Buzzer(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

/**
 * @brief Generates a tone on the buzzer.
 * @param frequency The frequency of the tone in Hertz.
 * @param duration The duration of the tone in milliseconds. If 0, the tone will continue until stopped.
 */
void Buzzer::buzz(unsigned int frequency, unsigned long duration) {
    duration == 0 ? tone(pin, frequency) : tone(pin, frequency, duration);
}

/**
 * @brief Stops the tone being generated on the buzzer.
 */
void Buzzer::stop() {
    noTone(pin);
}
