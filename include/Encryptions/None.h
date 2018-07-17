
#ifndef ENCRYPTION_NONE_H
#define ENCRYPTION_NONE_H

#define ENCRYPTION_NONE_NAME "NONE"
#define ENCRYPTION_NONE_ENCRYPT &Encryption_None_Encrypt
#define ENCRYPTION_NONE_DECRYPT &Encryption_None_Decrypt
#define ENCRYPTION_NONE_VERIFY &Encryption_None_Verify

uint8_t Encryption_None_Encrypt (DataStream input, DataStream *output);
uint8_t Encryption_None_Decrypt (DataStream input, DataStream *output);
uint8_t Encryption_None_Verify (DataStream stream);

#endif
