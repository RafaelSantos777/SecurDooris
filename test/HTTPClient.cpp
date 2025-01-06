#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Redmi do Pedro";
const char* password = "ahnaosei";
const String imageUploadURL = "localhost:1880/upload";
HTTPClient httpClient;

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
    connectToWiFi();
    httpClient.begin(imageUploadURL);
}

void loop() {
    httpClient.addHeader("Content-Type", "image/jpeg");
    int httpResponseCode = httpClient.POST("I hecking love Node-RED!");
    Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    //    httpClient.end();
    delay(5000);
}
