#include <Arduino.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

SecurDoorisMQTTClient mqttClient;

void loopDelay() {
    static int lastPoint = millis();
    if (millis() - lastPoint > 1000) {
        Serial.print("."); lastPoint = millis();
    }
}

void setup() {
    delay(5000);
    Serial.begin(115200);
    Serial1.begin(9600);
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
        Serial1.println(message);
        Serial.println("\nReceived message from MQTT: " + message);
    }
    if (Serial1.available()) {
        if (IN_UNO_DEBUG_MODE) {
            String input = Serial1.readString();
            String nfc = input.substring(1, input.length());
            if (input.charAt(0) == NFC) input = String(NFC);
            switch (input.toInt()) {
            case TURN_ON_LIGHT:
                digitalWrite(LED_BUILTIN, HIGH);
                mqttClient.sendMessage(TURN_ON_LIGHT, CAMERA_COMMANDS_TOPIC);
                break;
            case TURN_OFF_LIGHT:
                digitalWrite(LED_BUILTIN, LOW);
                mqttClient.sendMessage(TURN_OFF_LIGHT, CAMERA_COMMANDS_TOPIC);
                break;
            case UPLOAD_HAND_PHOTO:
                mqttClient.sendMessage(UPLOAD_HAND_PHOTO, CAMERA_COMMANDS_TOPIC);
                break;
            case NFC:
                Serial.println("\nIn Uno Debug Mode, message was detected as NFC, but could have been missunderstood");
                mqttClient.sendMessage(nfc, NFC_READINGS_TOPIC);
                break;
            default:
                Serial.println("\n\tReceived message from Uno \n" + input);
                break;
            }
        }
        else
            switch (Serial1.read()) {
            case TURN_ON_LIGHT:
                mqttClient.sendMessage(TURN_ON_LIGHT, CAMERA_COMMANDS_TOPIC);
                break;
            case TURN_OFF_LIGHT:
                mqttClient.sendMessage(TURN_OFF_LIGHT, CAMERA_COMMANDS_TOPIC);
                break;
            case UPLOAD_HAND_PHOTO:
                mqttClient.sendMessage(UPLOAD_HAND_PHOTO, CAMERA_COMMANDS_TOPIC);
                break;
            case NFC:
                mqttClient.sendMessage(Serial1.readString(), NFC_READINGS_TOPIC);
                break;
            default:
                Serial.println("\n\tReceived something from Uno, but it ain't a BOARDCOMMAND\n");
                break;
            }
    }




    if (IN_UNO_DEBUG_MODE) {
        loopDelay();
    }
    else delay(10);
}