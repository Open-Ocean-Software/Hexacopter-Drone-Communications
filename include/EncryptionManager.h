
#ifndef ENCRYPTIONMANAGER_H
#define ENCRYPTIONMANAGER_H

#include "DataStream.h"
#include <stdint.h>

uint8_t SetEncryption (char encryption[]);

uint8_t Encrypt (DataStream input, DataStream *output);
uint8_t Decrypt (DataStream input, DataStream *output);
uint8_t VerifyCrypt (DataStream stream);

#endif
