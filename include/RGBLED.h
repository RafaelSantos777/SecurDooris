#include <Color.h>


enum Durations { //TODO test
    ON = 0,
    ALARM = 300,
    THINKING = 100,
};


class RGBLED {

public:
    RGBLED(int redPin, int greenPin, int bluePin);
    void setColor(Color color, unsigned long duration = 0);
    void setColorBlink(Color color, unsigned long duration = 0, long blinkDuration = 0, bool fade = false);
    void update();

private:

    void set(Color color);
    const int redPin;
    const int greenPin;
    const int bluePin;
    unsigned long endTime = 0;
    unsigned long setTime = 0;
    unsigned long loopTime = 0;
    Color currentColor;
    bool fadeBlink;
    bool on;
};

