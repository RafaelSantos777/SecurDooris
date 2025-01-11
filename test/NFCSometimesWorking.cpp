#include "NfcAdapter.h"
#include "PN532_I2C.h"
#include <PN532.h>
#include <Wire.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
void setup() {
    delay(7000);
    Serial.begin(115200);
    Serial.println("Arduino Nano 33 IoT - Started");
    nfc.begin();
}

void loop() {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent()) {
        NfcTag tag = nfc.read();
        Serial.println(tag.getUidString());
    }
    delay(5000);
}