
#ifndef CHECKSUMHELPER_H
#define CHECKSUMHELPER_H

#include "../DataStream.h"
#include <stdint.h>

#define CHECKSUMSTREAMLENGTH 2

DataStream GenerateCheckSumStream (DataStream input);

uint8_t VerifyCheckSumStream (DataStream stream, DataStream cs);

#endif
