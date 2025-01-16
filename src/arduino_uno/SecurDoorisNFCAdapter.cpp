#include <SecurDoorisNFCAdapter.h>

// This file contains the implementation of functions for interacting with an NFC adapter.
// It includes functions to read NFC tag IDs, block or unblock the tag reader, and check if the tag reader is blocked.

bool readerBlocked = true;

/**
 * @brief Reads the NFC tag ID.
 * @param nfc The NFC adapter instance.
 * @return The NFC tag ID as a string.
 */
String readTagId(NfcAdapter nfc) {
    NfcTag nfcTag = nfc.read();
    return nfcTag.getUidString();
}

/**
 * @brief Blocks or unblocks the tag reader.
 * @param block If true, blocks the tag reader; otherwise, unblocks it.
 */
void blockTagReader(bool block)
{
    readerBlocked = block;
}

/**
 * @brief Checks if the tag reader is blocked.
 * @return True if the tag reader is blocked, false otherwise.
 */
bool tagReaderBlocked()
{
    return readerBlocked;
}
