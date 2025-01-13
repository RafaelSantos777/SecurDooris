#include <Arduino.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

SecurDoorisMQTTClient mqttClient;


int lastPoint = millis();
const int TIME_BETWEEN_POINTS = 1000;

void loopDelay(bool debug = true) {
    if (debug) {
        if (millis() - lastPoint > TIME_BETWEEN_POINTS) {
            Serial.print("."); lastPoint = millis();
        }
    }
    delay(10);
}

void setup() {
    delay(5000);
    Serial.begin(115200);
    Serial1.begin(9600);
    Serial.println("Arduino Nano 33 IoT - Started Setup");
    connectToWiFi();
    mqttClient.connect(MQTT_BROKER);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Arduino Nano 33 IoT - Finished Setup");
}

void loop() {
    mqttClient.poll();
    if (Serial1.available()) {
        String input = Serial1.readString();
        switch (input.toInt()) {
        case TURN_ON_LIGHT:
            Serial.println("Turning on light");
            digitalWrite(LED_BUILTIN, HIGH);
            break;
        case TURN_OFF_LIGHT:
            Serial.println("Turning off light");
            digitalWrite(LED_BUILTIN, LOW);
            break;
        case UPLOAD_HAND_PHOTO:
            break;
        case UPLOAD_INTRUDER_PHOTO:
            break;
        default:
            Serial.println("\n\tReceived message from Uno \n" + input);
            break;
        }
    }
    if (Serial.available()) {
        String input = Serial.readString();
        Serial.print("\nYou wrote '" + input + "', sending it to Uno...");
        Serial1.print(input);
    }
    loopDelay();
}

// mqttClient.sendMessage(TURN_ON_LIGHT, "camera/light");