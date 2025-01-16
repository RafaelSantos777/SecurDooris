#include <InternetCommunication.h>

/**
 * @file InternetCommunication.cpp
 * @brief Implementation of the SecurDoorisMQTTClient class and WiFi connection functions.
 *
 * This file contains the implementation of the SecurDoorisMQTTClient class,
 * which is used to manage MQTT communication for the SecurDooris system.
 * It also includes functions to connect to WiFi.
 */

 /**
  * @brief Constructor for SecurDoorisMQTTClient class.
  */
SecurDoorisMQTTClient::SecurDoorisMQTTClient() : MqttClient(wifiClient) {}

/**
 * @brief Connects to the specified MQTT broker.
 * @param broker The MQTT broker address.
 * @param port The MQTT broker port.
 */
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

/**
 * @brief Reconnects to the MQTT broker if disconnected and resubscribes.
 * @param broker The MQTT broker address.
 * @param topic The MQTT topic to subscribe to.
 * @param port The MQTT broker port.
 */
void SecurDoorisMQTTClient::reconnectIfDisconnected(const char broker[], String topic, int port) {
    if (!connected()) {
        Serial.println("MQTT - Got disconnected");
        if (MqttClient::connect(broker, port)) {
            subscribe("SecurDooris/" + topic);
            Serial.println("MQTT - Reconnected");

        }
    }
}

/**
 * @brief Sends a message to the specified MQTT topic.
 * @param message The message to send.
 * @param topic The MQTT topic to send the message to.
 * @param qos The Quality of Service level for the message.
 */
void SecurDoorisMQTTClient::sendMessage(String message, String topic, int qos)
{
    Serial.print("MQTT - Sending message '" + message + "' to topic 'SecurDooris/" + topic + "'...");
    beginMessage("SecurDooris/" + topic, false, qos);
    print(message);
    endMessage();
    Serial.println(" Message Sent");
}
/**
 * @brief Variation for 'int's
 */
void SecurDoorisMQTTClient::sendMessage(int message, String topic, int qos) {
    sendMessage(String(message), topic, qos);
}

/**
 * @brief Connects to the WiFi network.
 * @param ssid The SSID of the WiFi network.
 * @param password The password of the WiFi network.
 */
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
