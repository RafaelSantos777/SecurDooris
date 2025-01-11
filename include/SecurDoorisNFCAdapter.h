#include "NfcAdapter.h"
#include "PN532_I2C.h"

class SecurDoorisNFCAdapter {

public:
    void begin();
    String readTagId();
    bool tagPresent();

private:
    NfcAdapter* nfc;
};
