
#include "Compressions/None.h"

uint8_t Compression_None_Compress (DataStream input, DataStream *output)
{
    output = &input;
}

uint8_t Compression_None_Decompress (DataStream input, DataStream *output)
{
    output = &input;
}
