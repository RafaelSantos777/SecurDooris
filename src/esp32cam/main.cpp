#include <WiFi.h>
#include <Camera.h>

Camera camera;

const char* ssid = "Redmi do Pedro";
const char* password = "ahnaosei";
const String uploadHandURL = "http://192.168.171.210:1880/upload_hand";
const String uploadIntruderURL = "http://192.168.171.210:1880/upload_intruder";

void connectToWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

void setup() {
    Serial.begin(115200);
    camera.begin();
    connectToWiFi();
}

void loop() {
    camera.uploadPhoto(uploadHandURL);
    delay(5000);
}
