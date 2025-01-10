#include <InternetCommunication.h>

void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

SecurDoorisMQTTClient::SecurDoorisMQTTClient() : MqttClient(wifiClient) {
}

void SecurDoorisMQTTClient::connect(const char* broker, int port) {
    if (!MqttClient::connect(broker, port)) {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(connectError());
        while (true);
    }
    Serial.println("Connected to MQTT Client");
}

void SecurDoorisMQTTClient::sendMessage(String message, String topic, int qos) {
    beginMessage(topic, false, qos);
    print(message);
    endMessage();
}
