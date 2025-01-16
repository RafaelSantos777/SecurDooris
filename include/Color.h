/**
 * @file Color.h
 * @brief Defines the Color structure and some predefined colors.
 */

 /**
  * @struct Color
  * @brief Represents a color using red, green, and blue components.
  */
typedef struct {
    int red;   ///< Red component of the color.
    int green; ///< Green component of the color.
    int blue;  ///< Blue component of the color.
} Color;


/// Predefined colors
const Color RED = { 255, 0, 0 };
const Color GREEN = { 0, 255, 0 };
const Color BLUE = { 0, 0, 255 };
const Color WHITE = { 120, 255, 240 };
const Color YELLOW = { 255, 255, 0 };
const Color CYAN = { 0, 255, 255 };
const Color MAGENTA = { 255, 0, 255 };
const Color OFF = { 0, 0, 0 };
