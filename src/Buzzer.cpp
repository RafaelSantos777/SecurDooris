#include <Buzzer.h>

Buzzer::Buzzer(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void Buzzer::buzz(unsigned int frequency, unsigned long duration) {
    duration > 0 ? tone(pin, frequency, duration) : tone(pin, frequency);
}

void Buzzer::stop() {
    noTone(pin);
}
