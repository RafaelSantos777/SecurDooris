#include <SecurDoorisNFCAdapter.h>

String readTagId(NfcAdapter nfc) {
    NfcTag nfcTag = nfc.read();
    return nfcTag.getUidString();
}