#include <Arduino.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>


const long PING_AND_LED_UPDATE_TIME_INTERVAL = 500;

bool isBuiltInLedOn = false;

SecurDoorisMQTTClient mqttClient;

void loopDelayAndPing() {
    static long lastPoint = millis();

    // Makes nano led change and pings uno according to the interval
    if (millis() - lastPoint > PING_AND_LED_UPDATE_TIME_INTERVAL) {
        digitalWrite(LED_BUILTIN, isBuiltInLedOn ? LOW : HIGH);
        isBuiltInLedOn = !isBuiltInLedOn;
        lastPoint = millis();
        Serial1.println(PING);
    }
    delay(10);
}

void setup() {
    delay(5000);
    Serial.begin(115200);
    Serial1.begin(9600);
    // Timeout to help the connection between nano and uno not getting stuck
    Serial1.setTimeout(200);

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
    // Function used to make sure it reconnects when connection is lost
    mqttClient.reconnectIfDisconnected(MQTT_BROKER, ARDUINO_COMMANDS_TOPIC);

    // Receives and sends mqqt messsages directly to uno
    if (mqttClient.available()) {
        String message = mqttClient.readString();
        Serial.println("Received: " + message);
        Serial1.println(message);
    }

    // Switch to send unos mqtt messages according to the desired goal of each command
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
        case NFC: { // After the command Uno sends the tag
            String nfc = Serial1.readStringUntil('\n');
            // Removes \n that doesn't show on Serial.println(), but shows on node-red;
            nfc.remove(nfc.length() - 1);
            mqttClient.sendMessage(nfc, NFC_READINGS_TOPIC);
            break;
        }
        default:
            Serial.println("Uno - " + input);
            break;
        }
    }

    loopDelayAndPing();
}