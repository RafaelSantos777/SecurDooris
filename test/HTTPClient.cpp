#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ssid";
const char* password = "pass";
const String imageUploadURL = "...node-red:1880/upload";
HTTPClient httpClient;
int count = 0;

void connectToWiFi() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

void setup() {
    delay(7000);
    Serial.begin(115200);
    Serial.println("Arduino Nano 33 IoT - Started");
    connectToWiFi();
    httpClient.begin(imageUploadURL);
}

void loop() {
    httpClient.addHeader("Content-Type", "text/plain");
    int httpResponseCode = httpClient.POST("I hecking love Node-RED!" + String(count++));
    Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    delay(500);
}
