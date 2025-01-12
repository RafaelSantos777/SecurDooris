#include <ArduinoMqttClient.h>
#if defined(ARDUINO_AVR_UNO)
#include <UnoWiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif


inline char* WIFI_SSID = "Redmi do Pedro";
inline char* WIFI_PASSWORD = "ahnaosei";


const char MQTT_BROKER[] = "f9bb39c5d7f044479e71d6922c6992e7.s1.eu.hivemq.cloud"; // TODO

const String mqtt_user = "wo";       //write only access broker
const String mqtt_password = "writeonly";

void connectToWiFi();

class SecurDoorisMQTTClient : public MqttClient {

public:
    SecurDoorisMQTTClient();
    void connect(const char broker[], int port = DEFAULT_PORT);
    void sendMessage(String message, String topic, int qos = DEFAULT_QOS);

private:
    static constexpr int DEFAULT_QOS = 2;
    static constexpr int DEFAULT_PORT = 8883;
    WiFiClient wifiClient;
};
