
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "DataStream.h"
#include <stdint.h>

#define ENCRYPTIONNAME_LENGTH 4

typedef struct {
    char Name [];
    uint8_t (*Encrypt) (DataStream input, DataStream *output);
    uint8_t (*Decrypt) (DataStream input, DataStream *output);
    uint8_t (*Verify) (DataStream stream);
} Encryption;

/**
 * Creates a new encryption algorithm object.
 * @param  name     The name of the encryption.
 * @param  encrypt  The encryption algorithm.
 * @param  decrypt  The decryption algorithm.
 * @param  verify   Verifies an encrypted message.
 * @return          A new encryption algorithm object.
 */
#define InitializeEncryption(name,encrypt,decrypt,verify) { .Name = name, .Encrypt = encrypt, .Decrypt = decrypt, .Verify = verify }

#endif
