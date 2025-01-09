#include <Arduino.h>
#define LED 4

void setup() {
    // switch off LED pin
    Serial.begin(9600);               // initialize serial communication at 9600 bits per second:
    Serial1.begin(9600);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    delay(10000);
    digitalWrite(LED, LOW);             // initialize UART with baud rate of 9600
    delay(4000);
}
void loop() {
    Serial.println(Serial1.available());
    while (Serial1.available()) {
        String receivedData = Serial1.readString();   // read one byte from serial buffer and save to receivedData
        Serial.println(receivedData);                // print receivedData to serial monitor
        if (receivedData == "amogus") {
            digitalWrite(LED, HIGH); // switch LED On
        }
        else if (receivedData == "sus") {
            digitalWrite(LED, LOW);  // switch LED Off
        }
    }
    delay(1000);
}
