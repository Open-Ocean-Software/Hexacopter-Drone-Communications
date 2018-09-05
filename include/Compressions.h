
#ifndef COMPRESSIONS_H
#define COMPRESSIONS_H

#include "Compression.h"
#include <stdint.h>

//////////////////////////
// Include Compressions //
//////////////////////////
#include "Compressions/None.h"

///////////////////////////
// Register Compressions //
///////////////////////////
#define COMPRESSION_LIST    InitializeCompression(COMPRESSION_NONE_NAME, COMPRESSION_NONE_COMPRESS, COMPRESSION_NONE_DECOMPRESS)

#define COMPRESSION_LIST_COUNT 1


extern Compression Compressions [];

/**
 * Finds the compression algorithm with the given name.
 * @param  name The name of the algorithm
 * @return      The compression algorithm
 */
Compression *FindCompression (char name[]);
/**
 * Tries to find the compression algorithm with the given name.
 * @param  name        The name of the algorithm
 * @param  compression The compression algorithm
 * @return             Success code
 */
uint8_t TryFindCompression (char name[], Compression *compression);
/**
 * Checks if the compression algorithm name exists.
 * @param  name The name of the algorithm.
 * @return      Whether or not the compression algorithm exists.
 */
uint8_t CompressionExists (char name[]);

#endif
