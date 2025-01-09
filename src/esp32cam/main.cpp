#include <Camera.h>
#include <Communication.h>

Camera camera;

void setup() {
    Serial.begin(9600);
    Serial.println("ESP32 CAM - Started");
    camera.begin();
    connectToWifi();
    connectToMQTTClient();
    mqttClient.subscribe(BOARD_COMMUNICATION_TOPIC, DEFAULT_MQTT_QOS);
}

void loop() {
    switch (mqttClient.read()) {
        int httpCode;
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
