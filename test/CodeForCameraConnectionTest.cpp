#include <Arduino.h>
#define LED 4

void setup() {
    pinMode(LED, OUTPUT);      // set LED pin as output
    digitalWrite(LED, LOW);    // switch off LED pin

    Serial1.begin(115200);            // initialize UART with baud rate of 9600
}
void loop() {
    while (Serial1.available() >= 0) {
        int receivedData = Serial1.read();   // read one byte from serial buffer and save to receivedData
        if (receivedData == 1) {
            digitalWrite(LED, HIGH); // switch LED On
        }
        else if (receivedData == 0) {
            digitalWrite(LED, LOW);  // switch LED Off
        }
    }
}