#include <SecurDorisNFCAdapter.h>

SecurDorisNFCAdapter::SecurDorisNFCAdapter() : NfcAdapter(pn532_i2c), pn532_i2c(Wire) {
    begin();
}

String SecurDorisNFCAdapter::getTagId() {
    NfcTag nfcTag = read();
    return nfcTag.getUidString();
}
