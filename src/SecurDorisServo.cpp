#include <SecurDorisServo.h>
#include <cmath>

SecurDoorisServo::SecurDoorisServo(int pin) {
    attach(pin);
}

void SecurDoorisServo::rotate(int degrees, unsigned long duration) {
    startDegrees = read();
    endDegrees = degrees;
    startTime = millis();
    endTime = startTime + duration;
}

void SecurDoorisServo::update() {
    unsigned long currentTime = millis();
    if (currentTime > endTime)
        return;
    float timeRatio = (currentTime - startTime) / (endTime - startTime);
    int currentDegrees = std::round(startDegrees + (endDegrees - startDegrees) * timeRatio);
    write(currentDegrees);
}
