#include <SecurDoorisNFCAdapter.h>
#include <Wire.h>

SecurDoorisNFCAdapter::SecurDoorisNFCAdapter() : NfcAdapter(pn532_i2c), pn532_i2c(Wire) {
    begin();
}

String SecurDoorisNFCAdapter::getTagId() {
    NfcTag nfcTag = read();
    return nfcTag.getUidString();
}
