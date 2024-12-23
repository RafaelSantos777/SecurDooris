#include <Arduino.h>

class Buzzer {
private:
    const int pin;
public:
    Buzzer(int pin);
    void buzz(unsigned int frequency, unsigned long duration = 0);
    void stop();
};
