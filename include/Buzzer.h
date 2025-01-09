class Buzzer {

public:
    Buzzer(int pin);
    void buzz(unsigned int frequency, unsigned long duration = 0);
    void stop();

private:
    const int pin;
};
