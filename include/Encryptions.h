
#ifndef ENCRYPTIONS_H
#define ENCRYPTIONS_H

#include "Encryption.h"
#include <stdint.h>

/////////////////////////
// Include Encryptions //
/////////////////////////
#include "Encryptions/None.h"

//////////////////////////
// Register Encryptions //
//////////////////////////
#define ENCRYPTION_LIST     InitializeEncryption(ENCRYPTION_NONE_NAME, ENCRYPTION_NONE_ENCRYPT, ENCRYPTION_NONE_DECRYPT, ENCRYPTION_NONE_VERIFY)

#define ENCRYPTION_LIST_COUNT 1


extern Encryption Encryptions [];

Encryption *FindEncryption (char name[]);
uint8_t TryFindEncryption (char name[], Encryption *encryption);
uint8_t EncryptionExists (char name[]);

#endif
