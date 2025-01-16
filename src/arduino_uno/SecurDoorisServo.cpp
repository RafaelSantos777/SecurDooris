#include <SecurDoorisServo.h>
#include <Arduino.h>
#include <math.h>

SecurDoorisServo::SecurDoorisServo(int pin) : pin(pin) {}

/**
 * @brief Initializes the servo motor.
 */
void SecurDoorisServo::begin() {
    Serial.println("Servo Motor - Starting...");
    attach(pin);
    write(-10);
    Serial.println("Servo Motor - Started");
}

/**
 * @brief Sets the rotatation the servo motor to a specific angle over a duration.
 * @param degrees The number of degrees to rotate.
 * @param duration The duration over which to rotate, in milliseconds.
 */
void SecurDoorisServo::rotate(int degrees, unsigned long duration) {
    startDegrees = read();
    endDegrees = startDegrees + degrees;
    startTime = millis();
    endTime = startTime + duration;
}

/**
 * @brief Updates the servo motor position based on the elapsed time.
 */
void SecurDoorisServo::update() {
    unsigned long currentTime = millis();
    if (currentTime > endTime) {
        return;
    }
    float timeRatio = ((float)currentTime - startTime) / (endTime - startTime);//
    int currentDegrees = round(startDegrees + (endDegrees - startDegrees) * timeRatio);
    write(currentDegrees);
}
