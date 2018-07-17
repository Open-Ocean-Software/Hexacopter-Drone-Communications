
#ifndef CRCHELPER_H
#define CRCHELPER_H

#include "../DataStream.h"
#include <stdint.h>

DataStream GenerateCRCStream (DataStream input);

uint8_t VerifyCRCStream (DataStream stream, DataStream crc);

#define CRCSTREAMLENGTH

#endif
