#include <Arduino.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

bool ledOn = false;

SecurDoorisMQTTClient mqttClient;

void loopDelay() {
    static int lastPoint = millis();
    if (millis() - lastPoint > 500) {
        digitalWrite(LED_BUILTIN, ledOn ? LOW : HIGH);
        ledOn = !ledOn;
        lastPoint = millis();
    }
}


void setup() {
    delay(5000);
    Serial.begin(115200);
    Serial1.begin(9600);
    Serial1.setTimeout(100);
    Serial.println("Arduino Nano 33 IoT - Started Setup");
    connectToWiFi();
    mqttClient.connect(MQTT_BROKER);
    mqttClient.subscribe("SecurDooris/" + ARDUINO_COMMANDS_TOPIC);
    Serial.println("MQTT - Subscribed to topic: SecurDooris/" + ARDUINO_COMMANDS_TOPIC);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Arduino Nano 33 IoT - Finished Setup");
}

void loop() {
    mqttClient.poll();
    if (mqttClient.available()) {
        String message = mqttClient.readString();
        Serial.println("Received: " + message);
        Serial1.println(message);
    }
    if (Serial1.available()) {
        String input = Serial1.readStringUntil('\n');

        switch (input.toInt()) {
        case TURN_ON_LIGHT:
            mqttClient.sendMessage(TURN_ON_LIGHT, CAMERA_COMMANDS_TOPIC);
            break;
        case TURN_OFF_LIGHT:
            mqttClient.sendMessage(TURN_OFF_LIGHT, CAMERA_COMMANDS_TOPIC);
            break;
        case UPLOAD_HAND_PHOTO:
            mqttClient.sendMessage(UPLOAD_HAND_PHOTO, CAMERA_COMMANDS_TOPIC);
            break;
        case UPDATE_SESSION:
            mqttClient.sendMessage("1", UPDATE_SESSION_TOPIC);
            break;
        case NFC:
            mqttClient.sendMessage(Serial1.readStringUntil('\n'), NFC_READINGS_TOPIC);
            break;
        default:
            Serial.println("Uno - " + input);
            break;
        }
    }

    if (IN_DEBUG_MODE) {
        loopDelay();
    }
    else delay(10);
}