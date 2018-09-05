
#ifndef ENCRYPTIONMANAGER_H
#define ENCRYPTIONMANAGER_H

#include "DataStream.h"
#include <stdint.h>

/**
 * Sets the encryption algorithm
 * @param  encryption The name of the encryption algorithm
 * @return            Success code
 */
uint8_t SetEncryption (char encryption[]);

/**
 * Encrypts the given data stream according to the selected algorithm.
 * @param  input  The input stream
 * @param  output The output stream
 * @return        Success code
 */
uint8_t Encrypt (DataStream input, DataStream *output);
/**
 * Decrypts the given data stream according to the selected algorithm.
 * @param  input  The input stream
 * @param  output The output stream
 * @return        Success code
 */
uint8_t Decrypt (DataStream input, DataStream *output);
/**
 * Verifies the given data stream is valid.
 * @param  stream The stream to validate
 * @return        The validity of the stream
 */
uint8_t VerifyCrypt (DataStream stream);

#endif
