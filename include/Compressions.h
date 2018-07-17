
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

Compression *FindCompression (char name[]);
uint8_t TryFindCompression (char name[], Compression *compression);
uint8_t CompressionExists (char name[]);

#endif
