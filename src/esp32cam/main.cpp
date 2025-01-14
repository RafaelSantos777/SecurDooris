#include <Camera.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

Camera camera;
SecurDoorisMQTTClient mqttClient;
const String UPLOAD_HAND_URL = "http://192.168.5.210:1880/upload_hand";
const String UPLOAD_INTRUDER_URL = "http://192.168.5.210:1880/upload_intruder";

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 CAM - Started Setup");
    camera.begin();
    connectToWiFi();
    mqttClient.connect(MQTT_BROKER);
    mqttClient.subscribe("SecurDooris/" + CAMERA_COMMANDS_TOPIC);
    Serial.println("MQTT - Subscribed to topic: SecurDooris/" + CAMERA_COMMANDS_TOPIC);
    Serial.println("ESP32 CAM - Finished Setup");
}

int httpCode;
void loop() {
    mqttClient.poll();
    if (mqttClient.available()) {
        switch (mqttClient.readString().toInt()) {
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
    }
    delay(100);
}
