
#include "EncryptionManager.h"
#include "Encryptions.h"

Encryption *currentEncryption = 0;

uint8_t SetEncryption (char encryption[])
{
    return TryFindEncryption(encryption, currentEncryption);
}

uint8_t Encrypt (DataStream input, DataStream *output)
{
    if (currentEncryption != 0) {
        return currentEncryption->Encrypt(input, output);
    }
    return 0x0;
}

uint8_t Decrypt (DataStream input, DataStream *output)
{
    if (currentEncryption != 0) {
        return currentEncryption->Decrypt(input, output);
    }
    return 0x0;
}

uint8_t VerifyCrypt (DataStream stream)
{
    if (currentEncryption != 0) {
        return currentEncryption->Verify(stream);
    }
    return 0x0;
}
