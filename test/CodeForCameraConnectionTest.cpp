#include <Arduino.h>
#define LED 4

void setup() {
    pinMode(LED, OUTPUT);      // set LED pin as output
    digitalWrite(LED, LOW);    // switch off LED pin

    Serial.begin(9600);            // initialize UART with baud rate of 9600
}
void loop() {
    while (Serial.available() >= 0) {
        String receivedData = Serial.readString();   // read one byte from serial buffer and save to receivedData
        if (receivedData == "amogus") {
            digitalWrite(LED, HIGH); // switch LED On
        }
        else if (receivedData == "sus") {
            digitalWrite(LED, LOW);  // switch LED Off
        }
    }
}
