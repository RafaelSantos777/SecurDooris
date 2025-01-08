#include <Arduino.h>
#include "esp_camera.h"
#include <HTTPClient.h>

class Camera {
public:
    void begin();
    void turnOnLight();
    void turnOffLight();
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
    HTTPClient httpClient;
    camera_config_t config;
};
