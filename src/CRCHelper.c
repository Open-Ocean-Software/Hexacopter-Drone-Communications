
#include "Helpers/CRCHelper.h"

//
// TODO: Write a CRC generator.
//

#define CRCSTREAMLENGTH 1

DataStream GenerateCRCStream (DataStream input)
{
    uint8_t data [] = { 0x00 };
    DataStream crc = InitializeDataStream(data, 1);
    return crc;
}

uint8_t VerifyCRCStream (DataStream stream, DataStream crc)
{
    if (crc.Data[0] == 0x00) {
        return 0x1;
    }
    return 0x0;
}
