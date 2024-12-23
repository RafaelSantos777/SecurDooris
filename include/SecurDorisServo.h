#include <Arduino.h>
#include <Servo.h>

class SecurDoorisServo : public Servo {
private:
    int startDegrees;
    int endDegrees;
    unsigned long startTime;
    unsigned long endTime;
public:
    SecurDoorisServo(int pin);
    void rotate(int degrees, long duration);
    void update();
};
