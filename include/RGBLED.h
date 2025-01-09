#include <Color.h>

class RGBLED {

public:
    RGBLED(int redPin, int greenPin, int bluePin);
    void setColor(Color color, unsigned long duration = 0);
    void update();

private:
    const int redPin;
    const int greenPin;
    const int bluePin;
    unsigned long endTime = 0;
};
