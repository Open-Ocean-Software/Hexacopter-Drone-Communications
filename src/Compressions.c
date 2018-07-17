
#include "Compressions.h"

Compression Compressions [COMPRESSION_LIST_COUNT] = { COMPRESSION_LIST };

Compression *FindCompression (char name[])
{
    Compression *comp = 0;
    TryFindCompression(name, comp);
    return comp;
}

uint8_t TryFindCompression (char name[], Compression *compression)
{
    for (int i = 0; i < COMPRESSION_LIST_COUNT; i++) {
        uint8_t match = 0x1;
        for (int j = 0; j < COMPRESSIONNAME_LENGTH; j++) {
            match &= (name[j] == Compressions[i].Name);
        }
        if (match) {
            compression = &(Compressions[i]);
            return 0x1;
        }
    }
    return 0x0;
}

uint8_t CompressionExists (char name[])
{
    Compression *comp = 0;
    return TryFindCompression(name, comp);
}
