#include <Arduino.h>
#include <RGBLED.h>
RGBLED rgbled(4, 5, 6);

void setup() {
    Serial.begin(9600);
    rgbled.setColor(OFF);
}
void loop() {

    if (Serial.available()) {
        String receivedData = Serial.readString();
        if (receivedData == "on")
            rgbled.setColor(GREEN);
        else if (receivedData == "off")
            rgbled.setColor(RED);
    }
    else {
        rgbled.setColor(BLUE);
        delay(100);
        rgbled.setColor(OFF);
    }
    delay(500);
}
