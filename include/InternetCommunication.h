#include <ArduinoMqttClient.h>
#if defined(ARDUINO_ARCH_SAMD)
#include <WiFiNINA.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

/**
 * @file InternetCommunication.h
 * @brief Defines the SecurDoorisMQTTClient class for handling MQTT communication.
 *
 * This file contains the definition of the SecurDoorisMQTTClient class,
 * which extends the MqttClient class. It provides methods for connecting to WiFi
 * and handling MQTT communication for the SecurDooris system.
 */

 // WiFi credentials
inline char* WIFI_SSID = "ssid";
inline char* WIFI_PASSWORD = "pass";

// MQTT topics
const String CAMERA_COMMANDS_TOPIC = "camera_commands";
const String ARDUINO_COMMANDS_TOPIC = "arduino_commands";
const String NFC_READINGS_TOPIC = "nfc_readings";
const String UPDATE_SESSION_TOPIC = "update_session";

// MQTT broker address
const char MQTT_BROKER[] = "test.mosquitto.org";

// MQTT credentials
const String mqtt_user = "rw";
const String mqtt_password = "readwrite";

/**
 * @brief Connects to the WiFi network.
 */
void connectToWiFi();

/**
 * @class SecurDoorisMQTTClient
 * @brief A class to handle MQTT communication for the SecurDooris system.
 */
class SecurDoorisMQTTClient : public MqttClient {

public:
    /**
     * @brief Constructs a SecurDoorisMQTTClient object.
     */
    SecurDoorisMQTTClient();

    /**
     * @brief Connects to the MQTT broker.
     * @param broker The address of the MQTT broker.
     * @param port The port to connect to (default is 1884).
     */
    void connect(const char broker[], int port = DEFAULT_PORT);

    /**
     * @brief Reconnects to the MQTT broker if disconnected.
     * @param broker The address of the MQTT broker.
     * @param topic The MQTT topic to subscribe to.
     * @param port The port to connect to (default is 1884).
     */
    void reconnectIfDisconnected(const char broker[], String topic, int port = DEFAULT_PORT);

    /**
     * @brief Sends a message to the specified MQTT topic.
     * @param message The message to send.
     * @param topic The MQTT topic to send the message to.
     * @param qos The Quality of Service level for the message (default is 1).
     */
    void sendMessage(String message, String topic, int qos = DEFAULT_QOS);

    //Integer Variant
    void sendMessage(int message, String topic, int qos = DEFAULT_QOS);

private:
    static constexpr int DEFAULT_QOS = 1; ///< Default Quality of Service level.
    static constexpr int DEFAULT_PORT = 1884; ///< Default port for MQTT communication.
    WiFiClient wifiClient; ///< WiFi client for network communication.
};
