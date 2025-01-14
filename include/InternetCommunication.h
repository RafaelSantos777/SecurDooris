#include <ArduinoMqttClient.h>
#if defined(ARDUINO_ARCH_SAMD)
#include <WiFiNINA.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif


inline char* WIFI_SSID = "Redmi do Pedro";
inline char* WIFI_PASSWORD = "ahnaosei";


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
