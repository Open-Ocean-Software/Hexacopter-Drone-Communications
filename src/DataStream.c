
#include "DataStream.h"

DataStream AppendStream (DataStream base, DataStream addition)
{
    uint8_t length = base.Length + addition.Length;
    uint8_t data [length];
    int baseSize = base.Length * sizeof(uint8_t);
    int additionSize = addition.Length * sizeof(uint8_t);
    memcpy(data, base.Data, baseSize);
    memcpy(data + baseSize, addition.Data, additionSize);
    DataStream stream = InitializeDataStream(data, length);
    return stream;
}
