
#include "Encryptions.h"

Encryption Encryptions [ENCRYPTION_LIST_COUNT] = { ENCRYPTION_LIST };

Encryption *FindEncryption (char name[])
{
    Encryption *encryption;
    TryFindEncryption(name, encryption);
    return encryption;
}

uint8_t TryFindEncryption (char name[], Encryption *encryption)
{
    for (int i = 0; i < ENCRYPTION_LIST_COUNT; i++) {
        uint8_t match = 0x1;
        for (int j = 0; j < ENCRYPTIONNAME_LENGTH; j++) {
            match &= (name[j] == Encryptions[i].Name[j]);
        }
        if (match) {
            encryption = &(Encryptions[i]);
            return 0x1;
        }
    }
    return 0x0;
}

uint8_t EncryptionExists (char name[])
{
    Encryption *encryption;
    return TryFindEncryption(name, encryption);
}
