
#include "CompressionManager.h"
#include "Compressions.h"

Compression *currentCompression = 0;

uint8_t SetCompression (char compression[])
{
    return TryFindCompression(compression, currentCompression);
}

uint8_t Compress (DataStream input, DataStream *output)
{
    if (currentCompression != 0) {
        return currentCompression->Compress(input, output);
    }
    return 0x0;
}

uint8_t Decompress (DataStream input, DataStream *output)
{
    if (currentCompression != 0) {
        return currentCompression->Decompress(input, output);
    }
    return 0x0;
}
