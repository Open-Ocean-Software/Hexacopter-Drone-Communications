
#ifndef COMPRESSIONMANAGER_H
#define COMPRESSIONMANAGER_H

#include "DataStream.h"
#include <stdint.h>

uint8_t SetCompression (char compression[]);

uint8_t Compress (DataStream input, DataStream *output);
uint8_t Decompress (DataStream input, DataStream *output);

#endif
