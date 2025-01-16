#include <Camera.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

/**
 * @file main.cpp
 * @brief Main control logic for the SecurDooris system running on an ESP32 CAM.
 *
 * This file contains its main code.
 * The system operates by receiving commands via MQTT and controlling the camera accordingly.
 *
 * Components:
 * - Camera
 * - MQTT Client
 *
 * Constants:
 * - URLs for uploading photos.
 *
 * Variables:
 * - State variables to manage the current session and system actions.
 *
 * Functions:
 * - setup(): Initializes the system and its components.
 * - loop(): Main loop that continuously checks for MQTT messages and controls the camera.
 */


const String UPLOAD_HAND_URL = "http://192.168.5.210:1880/upload_hand";
const String UPLOAD_INTRUDER_URL = "http://192.168.5.210:1880/upload_intruder";
int httpCode;
Camera camera;
SecurDoorisMQTTClient mqttClient;

/**
 * @brief Initializes the system and its components.
 */
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


/**
 * @brief Main loop that continuously checks for MQTT messages and controls the camera.
 */
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
