#include <SecurDoorisNFCAdapter.h>

bool readerBlocked = true;

String readTagId(NfcAdapter nfc) {
    NfcTag nfcTag = nfc.read();
    return nfcTag.getUidString();
}

void blockTagReader(bool block)
{
    readerBlocked = block;
}

bool tagReaderBlocked()
{
    return readerBlocked;
}
