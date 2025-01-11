#include <ArduinoMqttClient.h>
#if defined(ARDUINO_AVR_UNO)
#include <UnoWiFi.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif


const char WIFI_SSID[] = "Redmi do Pedro";
const char WIFI_PASSWORD[] = "ahnaosei";

const char MQTT_BROKER[] = "?????"; // TODO

void connectToWiFi();

class SecurDoorisMQTTClient : public MqttClient {

public:
    SecurDoorisMQTTClient();
    void connect(const char broker[], int port = DEFAULT_PORT);
    void sendMessage(String message, String topic, int qos = DEFAULT_QOS);

private:
    static constexpr int DEFAULT_QOS = 1;
    static constexpr int DEFAULT_PORT = 1883;
    WiFiClient wifiClient;
};
