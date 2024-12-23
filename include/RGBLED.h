#include <Arduino.h>
#include <Color.h>

class RGBLED {
private:
    const int redPin;
    const int greenPin;
    const int bluePin;
    unsigned long endTime;
public:
    RGBLED(int redPin, int greenPin, int bluePin);
    void setColor(Color color, unsigned long duration = 0);
    void update();
    void resetTimer();
};
