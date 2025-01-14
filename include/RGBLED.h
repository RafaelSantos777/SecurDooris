#include <Color.h>


enum LIGHTTYPE { //TODO test
    ON = 0,
    ALARM = 100,
    THINKING = 500,
};


class RGBLED {

public:
    RGBLED(int redPin, int greenPin, int bluePin);
    void setColor(Color color, unsigned long duration = 0, LIGHTTYPE lightType = ON);
    void update();

private:
    const int redPin;
    const int greenPin;
    const int bluePin;
    unsigned long endTime = 0;
};

