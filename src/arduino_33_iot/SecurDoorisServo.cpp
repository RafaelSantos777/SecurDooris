#include <SecurDoorisServo.h>
#include <cmath>

SecurDoorisServo::SecurDoorisServo(int pin) {
    attach(pin);
    write(0);
}

void SecurDoorisServo::rotate(int degrees, unsigned long duration) {
    startDegrees = read();
    endDegrees = startDegrees + degrees;
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
