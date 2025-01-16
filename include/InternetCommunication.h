#include <ArduinoMqttClient.h>
#if defined(ARDUINO_ARCH_SAMD)
#include <WiFiNINA.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif


inline char* WIFI_SSID = "ssid";
inline char* WIFI_PASSWORD = "pass";

const String CAMERA_COMMANDS_TOPIC = "camera_commands";
const String ARDUINO_COMMANDS_TOPIC = "arduino_commands";
const String NFC_READINGS_TOPIC = "nfc_readings";
const String UPDATE_SESSION_TOPIC = "update_session";


const char MQTT_BROKER[] = "test.mosquitto.org";

const String mqtt_user = "rw";
const String mqtt_password = "readwrite";

void connectToWiFi();

class SecurDoorisMQTTClient : public MqttClient {

public:
    SecurDoorisMQTTClient();
    void connect(const char broker[], int port = DEFAULT_PORT);
    void sendMessage(String message, String topic, int qos = DEFAULT_QOS);
    void sendMessage(int message, String topic, int qos = DEFAULT_QOS);

private:
    static constexpr int DEFAULT_QOS = 1;
    static constexpr int DEFAULT_PORT = 1884;
    WiFiClient wifiClient;
};
