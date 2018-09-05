
#ifndef COMPRESSIONMANAGER_H
#define COMPRESSIONMANAGER_H

#include "DataStream.h"
#include <stdint.h>

/**
 * Sets the current compression algorithm
 * @param  compression The name of the compression algorithm
 * @return             Success code
 */
uint8_t SetCompression (char compression[]);

/**
 * Compresses a data stream according to the current algorithm
 * @param  input  The input stream
 * @param  output The output stream
 * @return        Success code
 */
uint8_t Compress (DataStream input, DataStream *output);
/**
 * Decompress a data stream according to the current algorithm
 * @param  input  The input stream
 * @param  output The output stream
 * @return        Success code
 */
uint8_t Decompress (DataStream input, DataStream *output);

#endif
