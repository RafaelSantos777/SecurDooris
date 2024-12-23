#include <Arduino.h>
#include <Servo.h>

class SecurDoorisServo : public Servo {
private:
    int startDegrees = 0;
    int endDegrees = 0;
    unsigned long startTime = 0;
    unsigned long endTime = 0;
public:
    SecurDoorisServo(int pin);
    void rotate(int degrees, unsigned long duration);
    void update();
};
