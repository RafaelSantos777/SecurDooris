class Buzzer {
    // This file defines the Buzzer class for controlling a buzzer module.
public:

    /**
     * @brief Constructs a Buzzer object.
     * @param pin The pin number where the buzzer is connected.
     */
    Buzzer(int pin);
    /**
     * @brief Starts the buzzer with a specified frequency and duration.
     * @param frequency The frequency of the buzzer sound in Hertz.
     * @param duration The duration for which the buzzer should sound in milliseconds (default is 0, which means indefinitely).
     */
    void buzz(unsigned int frequency, unsigned long duration = 0);
    /**
     * @brief Stops the buzzer.
     */
    void stop();

private:
    const int pin; ///< The pin number where the buzzer is connected.
};
