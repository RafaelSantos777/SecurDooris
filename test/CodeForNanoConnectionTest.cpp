#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);      // set LED pin as output
  digitalWrite(LED_BUILTIN, LOW);    // switch off LED pin

  Serial.begin(115200);               // initialize serial communication at 9600 bits per second:
  Serial1.begin(115200);            // initialize UART with baud rate of 9600
}
void loop() {
  if (Serial.read() == '1') {
    Serial1.write((byte)1);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LEDS ON");
  }
  else if (Serial.read() == '0') {
    Serial1.write((byte)0);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LEDS OFF");
  }
}