#include <Camera.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

Camera camera;
const String UPLOAD_HAND_URL = "http://192.168.171.210:1880/upload_hand";
const String UPLOAD_INTRUDER_URL = "http://192.168.171.210:1880/upload_intruder";

void setup() {
    Serial.begin(9600);
    Serial.println("ESP32 CAM - Started");
    camera.begin();
    connectToWiFi();
}

void loop() {
    int httpCode;
    switch (Serial1.read()) {
    case -1:
        break;
    case TURN_ON_LIGHT:
        camera.turnOnLight();
        break;
    case TURN_OFF_LIGHT:
        camera.turnOffLight();
        break;
    case UPLOAD_HAND_PHOTO:
        httpCode = camera.uploadPhoto(UPLOAD_HAND_URL);
        if (httpCode != HTTP_CODE_OK)
            Serial.printf("Hand photo upload unsuccessful. HTTP code: %d\n", httpCode);
        break;
    case UPLOAD_INTRUDER_PHOTO:
        httpCode = camera.uploadPhoto(UPLOAD_INTRUDER_URL);
        if (httpCode != HTTP_CODE_OK)
            Serial.printf("Intruder photo upload unsuccessful. HTTP code: %d\n", httpCode);
        break;
    }
    delay(10);
}
