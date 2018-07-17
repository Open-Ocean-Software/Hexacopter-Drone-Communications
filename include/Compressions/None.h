
#ifndef COMPRESSION_NONE_H
#define COMPRESSION_NONE_H

#define COMPRESSION_NONE_NAME "NONE"
#define COMPRESSION_NONE_COMPRESS &Compression_None_Compress
#define COMPRESSION_NONE_DECOMPRESS &Compression_None_Decompress

uint8_t Compression_None_Compress (DataStream input, DataStream *output);
uint8_t Compression_None_Decompress (DataStream input, DataStream *output);

#endif
