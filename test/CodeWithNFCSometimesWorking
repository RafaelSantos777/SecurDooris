#include "NfcAdapter.h"
#include "PN532_I2C.h"
#include <PN532.h>
#include <Wire.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
void setup() {
    Serial.begin(115200);
    nfc.begin();
}

void loop() {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent()) {
        NfcTag tag = nfc.read();
        tag.print();
    }
    delay(5000);
}