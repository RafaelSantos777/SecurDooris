#include <Camera.h>

void Camera::begin() {
    Serial.println("Camera Setup - Starting...");
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_VGA;
    config.pixel_format = PIXFORMAT_JPEG;
    config.grab_mode = CAMERA_GRAB_LATEST;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 2;

    //TODO apagar código comentado se nunca for usado
    // if (config.pixel_format == PIXFORMAT_JPEG) {
    //     if (psramFound()) {
    //         config.jpeg_quality = 10;
    //         config.fb_count = 2;
    //         config.grab_mode = CAMERA_GRAB_LATEST;
    //     }
    //     else {
    //         // Limit the frame size when PSRAM is not available
    //         config.frame_size = FRAMESIZE_SVGA;
    //         config.fb_location = CAMERA_FB_IN_DRAM;
    //     }
    // }
    // else {
    //     // Best option for face detection/recognition
    //     config.frame_size = FRAMESIZE_240X240;

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x\n", err);
        while (true);
    }
    pinMode(LED_PIN, OUTPUT);
    Serial.println("Camera Setup - Done");
}

void Camera::turnOnLight() {
    digitalWrite(LED_PIN, HIGH);
}

void Camera::turnOffLight() {
    digitalWrite(LED_PIN, LOW);
}

int Camera::uploadPhoto(String url) {
    camera_fb_t* frameBuffer = esp_camera_fb_get();
    httpClient.begin(url);
    httpClient.addHeader("Content-Type", "image/jpeg");
    int httpCode = httpClient.POST(frameBuffer->buf, frameBuffer->len);
    esp_camera_fb_return(frameBuffer);
    httpClient.end();
    return httpCode;
}
