#include <SecurDoorisNFCAdapter.h>


unsigned long blockEndTime = 0;

String readTagId(NfcAdapter nfc) {
    NfcTag nfcTag = nfc.read();
    return nfcTag.getUidString();
}


void blockReadings(unsigned long duration)
{
    blockEndTime = millis() + duration;
}

bool readingsBlocked()
{
    return millis() < blockEndTime;
}
