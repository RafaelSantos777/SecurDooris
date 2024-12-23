#include <Arduino.h>

class Buzzer {
private:
    const int pin;
public:
    Buzzer(int pin);
    void buzz(int frequency);
    void buzz(int frequency, long duration);
    void stop();
};
