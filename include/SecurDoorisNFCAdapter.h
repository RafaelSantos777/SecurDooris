#include "NfcAdapter.h"
#include "PN532_I2C.h"

class SecurDoorisNFCAdapter : public NfcAdapter {
private:
    PN532_I2C pn532_i2c;
public:
    SecurDoorisNFCAdapter();
    String getTagId();
};
