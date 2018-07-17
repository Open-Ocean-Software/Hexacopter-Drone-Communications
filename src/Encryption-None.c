
#include "Encryptions/None.h"

uint8_t Encryption_None_Encrypt (DataStream input, DataStream *output)
{
    output = &input;
}

uint8_t Encryption_None_Decrypt (DataStream input, DataStream *output)
{
    output = &input;
}

uint8_t Encryption_None_Verify (DataStream stream)
{
    return 0x01;
}
