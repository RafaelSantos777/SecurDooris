#include <ArduinoMqttClient.h>

extern MqttClient mqttClient;
const String BOARD_COMMUNICATION_TOPIC = "?????"; // TODO
const int DEFAULT_MQTT_QOS = 1;

enum Command {
    TURN_ON_LIGHT,
    TURN_OFF_LIGHT,
    UPLOAD_HAND_PHOTO,
    UPLOAD_INTRUDER_PHOTO
};

void connectToWiFi();
void connectToMQTTClient();
void sendMQTTMessage(String message, String topic, int qos = DEFAULT_MQTT_QOS);
void sendMQTTMessage(Command message, String topic, int qos = DEFAULT_MQTT_QOS);
