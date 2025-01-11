#include <SecurDoorisServo.h>
#include <Arduino.h>
#include <math.h>

SecurDoorisServo::SecurDoorisServo(int pin) : pin(pin) {}

void SecurDoorisServo::begin() {
    Serial.println("Servo Motor - Starting...");
    attach(pin);
    write(0);//TODO make sure this is diferent from the open door position
    Serial.println("Servo Motor - Done");
}

void SecurDoorisServo::rotate(int degrees, unsigned long duration) {
    startDegrees = read();
    endDegrees = startDegrees + degrees;
    startTime = millis();
    endTime = startTime + duration;
}

void SecurDoorisServo::update() {
    unsigned long currentTime = millis();
    if (currentTime > endTime) {
        Serial.println("less");
        return;
    }
    float timeRatio = ((float)currentTime - startTime) / (endTime - startTime);//
    int currentDegrees = round(startDegrees + (endDegrees - startDegrees) * timeRatio);
    write(currentDegrees);
}
