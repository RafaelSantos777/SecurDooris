#include <SecurDoorisNFCAdapter.h>
#include <Wire.h>

void SecurDoorisNFCAdapter::begin() {

    Serial.println("NFC Adapter - Starting...");
    PN532_I2C pn532_i2c(Wire);
    nfc = new NfcAdapter(pn532_i2c);
    nfc->begin(false);

    Serial.println("NFC Adapter - Done");
}

String SecurDoorisNFCAdapter::readTagId() {
    NfcTag nfcTag = nfc->read();
    return nfcTag.getUidString();
}


bool SecurDoorisNFCAdapter::tagPresent() {
    return nfc->tagPresent();
}