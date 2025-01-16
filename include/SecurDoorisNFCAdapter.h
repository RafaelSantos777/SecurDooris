#include "NfcAdapter.h"
#include "PN532_I2C.h"
#include <Wire.h>

/**
 * @file SecurDoorisNFCAdapter.h
 * @brief Defines functions for handling NFC tag reading and blocking.
 *
 * This file contains the declarations for functions to read NFC tag IDs
 * and to block or unblock the NFC tag reader.
 */

 // PN532 I2C interface
inline PN532_I2C pn532_i2c(Wire);

/**
 * @brief Reads the ID of an NFC tag.
 * @param nfc The NFC adapter to use for reading the tag.
 * @return The ID of the NFC tag as a string.
 */
String readTagId(NfcAdapter nfc);

/**
 * @brief Blocks or unblocks the NFC tag reader.
 * @param block Set to true to block the reader, false to unblock (default is true).
 */
void blockTagReader(bool block = true);

/**
 * @brief Checks if the NFC tag reader is blocked.
 * @return True if the reader is blocked, false otherwise.
 */
bool tagReaderBlocked();