#include <Servo.h>

/**
 * @file SecurDoorisServo.h
 * @brief Defines the SecurDoorisServo class for controlling the servo motor.
 *
 * This file contains the definition of the SecurDoorisServo class,
 * which extends the Servo class to provide methods for rotating the servo
 * to a specified angle over a specified duration.
 */

 /**
  * @class SecurDoorisServo
  * @brief A class to control a servo motor.
  */
class SecurDoorisServo : public Servo {

public:
    /**
     * @brief Constructs a SecurDoorisServo object.
     * @param pin The pin number where the servo is connected.
     */
    SecurDoorisServo(int pin);

    /**
     * @brief Initializes the servo.
     */
    void begin();

    /**
     * @brief Sets the rotation the servo motor to a specific angle over a duration.
     * @param degrees The angle to rotate the servo to.
     * @param duration The duration over which to rotate the servo (in milliseconds).
     */
    void rotate(int degrees, unsigned long duration);

    /**
     * @brief Updates the state of the servo.
     */
    void update();

private:
    int pin; ///< The pin number where the servo is connected.
    int startDegrees = 0; ///< The starting angle of the servo.
    int endDegrees = 0; ///< The ending angle of the servo.
    unsigned long startTime = 0; ///< The start time of the rotation.
    unsigned long endTime = 0; ///< The end time of the rotation.
};
