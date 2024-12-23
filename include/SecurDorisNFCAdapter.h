#include "NfcAdapter.h"
#include "PN532_I2C.h"
#include <Wire.h>

class SecurDorisNFCAdapter : public NfcAdapter {
private:
    PN532_I2C pn532_i2c;
public:
    SecurDorisNFCAdapter();
    String getTagId();
};
