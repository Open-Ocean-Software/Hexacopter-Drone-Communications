
#ifndef DATASTREAM_H
#define DATASTREAM_H

#include <stdint.h>

typedef struct {
    uint8_t *Data;
    unsigned int Length;
} DataStream;

/**
 * Creates a new data stream.
 * @param  data   A string of bytes (pointer).
 * @param  length The length of the string.
 * @return        A new DataStream.
 */
#define InitializeDataStream(data,length) { .Data = data, .Length = length }

/**
 * Appends a data stream to the end of another.
 * @param  base     The base data stream.
 * @param  addition The stream to append.
 * @return          The resultant data stream.
 */
DataStream AppendStream (DataStream base, DataStream addition);

#endif
