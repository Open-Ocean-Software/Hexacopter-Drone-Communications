
#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "DataStream.h"
#include <stdint.h>

#define COMPRESSIONNAME_LENGTH 4

typedef struct {
    char Name [];
    uint8_t (*Compress) (DataStream input, DataStream *output);
    uint8_t (*Decompress) (DataStream input, DataStream *output);
} Compression;

/**
 * Creates a new compression algorithm object.
 * @param  name       The name of the compression algorithm.
 * @param  compress   The compression algorithm function.
 * @param  decompress The decompression algorithm function.
 * @return            The compression algorithm object.
 */
#define InitializeCompression(name,compress,decompress) { .Name = name, .Compress = compress, .Decompress = decompress }

#endif
