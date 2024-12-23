#include <Buzzer.h>

Buzzer::Buzzer(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void Buzzer::buzz(int frequency) {
    tone(pin, frequency);
}

void Buzzer::buzz(int frequency, long duration) {
    tone(pin, frequency, duration);
}

void Buzzer::stop() {
    noTone(pin);
}
