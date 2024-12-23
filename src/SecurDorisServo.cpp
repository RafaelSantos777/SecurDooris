#include <SecurDorisServo.h>

SecurDoorisServo::SecurDoorisServo(int pin) {
    attach(pin);
}

void SecurDoorisServo::rotate(int degrees, long duration) {
    startDegrees = read();
    endDegrees = degrees;
    startTime = millis();
    endTime = startTime + duration;
}

void SecurDoorisServo::update() {
    unsigned long currentTime = millis();
    if (currentTime > endTime)
        return;
    long timeRatio = (currentTime - startTime) / (endTime - startTime);
    int currentDegrees = startDegrees + (endDegrees - startDegrees) * timeRatio;
    write(currentDegrees);
}
