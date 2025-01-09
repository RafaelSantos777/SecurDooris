#include <Arduino.h>
#define LED 4

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
}
void loop() {
    Serial.println(Serial1.available());
    if (Serial1.available()) {
        String receivedData = Serial1.readString();
        Serial.println(receivedData);
        if (receivedData == "on")
            digitalWrite(LED, HIGH);
        else if (receivedData == "off")
            digitalWrite(LED, LOW);

    }
    delay(100);
}
