#include <Communication.h>
#if defined(ARDUINO_SAMD_NANO_33_IOT)
#include <WiFiNINA.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

MqttClient mqttClient(new WiFiClient());

const char* WIFI_SSID = "Redmi do Pedro";
const char* WIFI_PASSWORD = "ahnaosei";
const char* MQTT_BROKER = "?????"; // TODO
const int MQTT_PORT = 1883;

void connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

void connectToMQTTClient() {
    if (!mqttClient.connect(MQTT_BROKER, MQTT_PORT)) {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(mqttClient.connectError());
        while (true);
    }
    Serial.println("Connected to MQTT Client");
}

void sendMQTTMessage(String message, String topic, int qos) {
    mqttClient.beginMessage(topic, false, qos);
    mqttClient.print(message);
    mqttClient.endMessage();
}

void sendMQTTMessage(Command message, String topic, int qos) {
    sendMQTTMessage((String)message, topic, qos);
}
