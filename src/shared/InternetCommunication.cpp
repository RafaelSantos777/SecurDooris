#include <InternetCommunication.h>


SecurDoorisMQTTClient::SecurDoorisMQTTClient() : MqttClient(wifiClient) {}

void SecurDoorisMQTTClient::connect(const char broker[], int port) {
    Serial.println("MQTT - Connecting to MQTT Client...");
    setUsernamePassword(mqtt_user, mqtt_password);
    if (!MqttClient::connect(broker, port)) {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(connectError());
        while (true);
    }
    Serial.println("MQTT - Connected to MQTT Client");
}

void SecurDoorisMQTTClient::reconnectIfDisconnected(const char broker[], String topic, int port) {
    if (!connected()) {
        Serial.println("MQTT - Got disconnected");
        if (MqttClient::connect(broker, port)) {
            subscribe("SecurDooris/" + topic);
            Serial.println("MQTT - Reconnected");

        }
    }
}

void SecurDoorisMQTTClient::sendMessage(String message, String topic, int qos)
{
    Serial.print("MQTT - Sending message '" + message + "' to topic 'SecurDooris/" + topic + "'...");
    beginMessage("SecurDooris/" + topic, false, qos);
    print(message);
    endMessage();
    Serial.println(" Message Sent");
}

void SecurDoorisMQTTClient::sendMessage(int message, String topic, int qos) {
    sendMessage(String(message), topic, qos);
}

void connectToWiFi()
{
    Serial.print("WiFi - Connecting to WiFi...");
    int status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
#if defined(ARDUINO_ARCH_SAMD)
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif
        Serial.print(".");
    }
    Serial.println("\nWiFi - Connected to WiFi");
}
