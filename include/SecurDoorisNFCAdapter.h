#include "NfcAdapter.h"
#include "PN532_I2C.h"
#include <Wire.h>

inline PN532_I2C pn532_i2c(Wire);

String readTagId(NfcAdapter nfc);