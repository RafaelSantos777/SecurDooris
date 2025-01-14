#include "NfcAdapter.h"
#include "PN532_I2C.h"
#include <Wire.h>

const int DEFAULT_BLOCK_NFC_TIME = 2000;

inline PN532_I2C pn532_i2c(Wire);

String readTagId(NfcAdapter nfc);

void blockReadings(unsigned long duration = DEFAULT_BLOCK_NFC_TIME);
bool readingsBlocked();