#include <Arduino.h>
#include <InternetCommunication.h>
#include <BoardCommands.h>

SecurDoorisMQTTClient mqttClient;



const int TIME_BETWEEN_POINTS = 1000;//TODO apagar dps de tudo a funcionar

void loopDelay() {//TODO apagar dps de tudo a funcionar
    static int lastPoint = millis();
    if (millis() - lastPoint > TIME_BETWEEN_POINTS) {
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
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Arduino Nano 33 IoT - Finished Setup");
}

void loop() {
    mqttClient.poll();
    if (Serial1.available()) {
        if (IN_UNO_DEBUG_MODE) {//TODO apagar dps de tudo a funcionar
            String input = Serial1.readString();
            switch (input.toInt()) {
            case TURN_ON_LIGHT:
                digitalWrite(LED_BUILTIN, HIGH);
                mqttClient.sendMessage(TURN_ON_LIGHT, "camera");
                break;
            case TURN_OFF_LIGHT:
                digitalWrite(LED_BUILTIN, LOW);
                mqttClient.sendMessage(TURN_OFF_LIGHT, "camera");
                break;
            case UPLOAD_HAND_PHOTO:
                mqttClient.sendMessage(UPLOAD_HAND_PHOTO, "camera");
                break;
            default:
                Serial.println("\n\tReceived message from Uno \n" + input);
                break;
            }
        }
        else {
            switch (Serial1.read()) {
            case TURN_ON_LIGHT:
                mqttClient.sendMessage(TURN_ON_LIGHT, "camera");
                break;
            case TURN_OFF_LIGHT:
                mqttClient.sendMessage(TURN_OFF_LIGHT, "camera");
                break;
            case UPLOAD_HAND_PHOTO:
                mqttClient.sendMessage(UPLOAD_HAND_PHOTO, "camera");
                break;
            default:
                Serial.println("\n\tReceived something from Uno, but it ain't a BOARDCOMMAND\n");
                break;
            }
        }
    }


    if (IN_UNO_DEBUG_MODE) {
        if (Serial.available()) {//TODO apagar dps de tudo a funcionar
            String input = Serial.readString();
            Serial.print("\nYou wrote '" + input + "', sending it to Uno...");
            Serial1.print(input);
        }
        loopDelay(); //TODO apagar dps de tudo a funcionar
    }
    else delay(10);
}