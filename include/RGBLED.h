#include <Color.h>

/**
 * @file RGBLED.h
 * @brief Defines the RGBLED class for controlling an RGB LED.
 *
 * This file contains the definition of the RGBLED class,
 * which provides methods to set the color of an RGB LED, make it blink,
 * and update its state.
 */
enum Durations { //
    ON = 0,
    ALARM = 300,
    THINKING = 100,
};

/**
 * @class RGBLED
 * @brief A class to control an RGB LED.
 */
class RGBLED {

public:
    /**
         * @brief Constructs an RGBLED object.
         * @param redPin The pin number for the red LED.
         * @param greenPin The pin number for the green LED.
         * @param bluePin The pin number for the blue LED.
         */
    RGBLED(int redPin, int greenPin, int bluePin);

    /**
     * @brief Sets the color of the RGB LED.
     * @param color The color to set.
     * @param duration The duration to keep the color (default is 0, which means indefinitely).
     */
    void setColor(Color color, unsigned long duration = 0);

    /**
     * @brief Sets the color of the RGB LED with blinking effect.
     * @param color The color to set.
     * @param duration The duration to keep the color (default is 0, which means indefinitely).
     * @param blinkDuration The duration of each blink (default is 0, which means no blinking).
     * @param fade Whether to fade the color in and out (default is false).
     */
    void setColorBlink(Color color, unsigned long duration = 0, long blinkDuration = 0, bool fade = false);

    /**
     * @brief Updates the state of the RGB LED.
     */
    void update();

private:
    /**
     * @brief Sets the color of the RGB LED.
     * @param color The color to set.
     */
    void set(Color color);

    const int redPin;   ///< The pin number for the red LED.
    const int greenPin; ///< The pin number for the green LED.
    const int bluePin;  ///< The pin number for the blue LED.
    unsigned long endTime = 0;   ///< The time when the color should end.
    unsigned long setTime = 0;   ///< The time when the color was set.
    unsigned long loopTime = 0;  ///< The time to blink.
    Color currentColor;          ///< The current color of the RGB LED.
    bool fadeBlink;              ///< Whether to fade the color.
    bool on;                     ///< Whether the LED is currently on.
};

