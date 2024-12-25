#include <Buzzer.h>

Buzzer::Buzzer(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void Buzzer::buzz(unsigned int frequency, unsigned long duration) {
    duration == 0 ? tone(pin, frequency) : tone(pin, frequency, duration);
}

void Buzzer::stop() {
    noTone(pin);
}
