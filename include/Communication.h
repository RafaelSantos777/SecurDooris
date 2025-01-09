#include <ArduinoMqttClient.h>
#if defined(ARDUINO_SAMD_NANO_33_IOT)
#include <WiFiNINA.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#endif

extern MqttClient mqttClient;
const String UPLOAD_HAND_URL = "http://192.168.171.210:1880/upload_hand";
const String UPLOAD_INTRUDER_URL = "http://192.168.171.210:1880/upload_intruder";
const String BOARD_COMMUNICATION_TOPIC = "?????"; // TODO
const int DEFAULT_MQTT_QOS = 1;

enum Command {
    TURN_ON_LIGHT,
    TURN_OFF_LIGHT,
    UPLOAD_HAND_PHOTO,
    UPLOAD_INTRUDER_PHOTO
};

void connectToWifi();
void connectToMQTTClient();
void sendMQTTMessage(String message, String topic, int qos = DEFAULT_MQTT_QOS);
void sendMQTTMessage(Command message, String topic, int qos = DEFAULT_MQTT_QOS);
