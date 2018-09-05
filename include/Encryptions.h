
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

/**
 * Finds the encryption algorithm with the given name.
 * @param  name The name of the encryption algorithm
 * @return      The selected encryption algorithm
 */
Encryption *FindEncryption (char name[]);
/**
 * Tries to find the encryption algorithm with the given name.
 * @param  name       The name of the encryption algorithm
 * @param  encryption The selected encryption algorithm
 * @return            Success code
 */
uint8_t TryFindEncryption (char name[], Encryption *encryption);
/**
 * Checks whether or not the encryption algorithm exists.
 * @param  name The name of the encryption algorithm
 * @return      Success code
 */
uint8_t EncryptionExists (char name[]);

#endif
