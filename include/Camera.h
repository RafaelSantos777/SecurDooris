#include <Arduino.h>
#include "esp_camera.h"
#include <HTTPClient.h>
// This file defines the Camera class for controlling the ESP32 camera module.

/**
 * @class Camera
 * @brief A class to control the ESP32 camera module.
 */
class Camera {

public:
    /**
     * @brief Initializes the camera with the specified configuration settings.
     */
    void begin();

    /**
     * @brief Turns on the camera's LED light.
     */
    void turnOnLight();

    /**
     * @brief Turns off the camera's LED light.
     */
    void turnOffLight();

    /**
     * @brief Uploads a photo to the specified URL.
     * @param url The URL to upload the photo to.
     * @return The HTTP response code from the server.
     */
    int uploadPhoto(String url);

private:
    static const int PWDN_GPIO_NUM = 32;
    static const int RESET_GPIO_NUM = -1;
    static const int XCLK_GPIO_NUM = 0;
    static const int SIOD_GPIO_NUM = 26;
    static const int SIOC_GPIO_NUM = 27;
    static const int Y9_GPIO_NUM = 35;
    static const int Y8_GPIO_NUM = 34;
    static const int Y7_GPIO_NUM = 39;
    static const int Y6_GPIO_NUM = 36;
    static const int Y5_GPIO_NUM = 21;
    static const int Y4_GPIO_NUM = 19;
    static const int Y3_GPIO_NUM = 18;
    static const int Y2_GPIO_NUM = 5;
    static const int VSYNC_GPIO_NUM = 25;
    static const int HREF_GPIO_NUM = 23;
    static const int PCLK_GPIO_NUM = 22;
    static const int LED_GPIO_NUM = 4;
    static const int RXp2 = 3;
    static const int TXp2 = 1;
    static const int LED_PIN = 4;
    HTTPClient httpClient; ///< HTTP client for uploading photos.
    camera_config_t config; ///< Configuration settings for the camera.
};
