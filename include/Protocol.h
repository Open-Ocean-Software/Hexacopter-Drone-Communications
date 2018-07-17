
#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "DataStream.h"
#include <stdint.h>

#define PROTOCOLNAME_LENGTH 4

typedef struct {
    char Name [];
    void (*Start) (void);
    void (*Stop) (void);
    void (*Encode) (ChunkCollection chunks)
    void (*Decode) (DataStream stream);
    DataStream (*Flush) (void);
    ChunkCollection (*State) (void);
} Protocol;

/**
 * Creates a new protocol.
 * @param  name     The name of the protocol.
 * @param  start    Executed on start.
 * @param  stop     Executed on stop.
 * @param  encode   The encoding algorithm that refreshes the encoding image matrix.
 * @param  decode   The decoding algorithm that refreshes the decoding image matrix.
 * @param  flush    Flushes the aggregate encoding message data stream.
 * @param  state    Gets the aggregate decoding state matrix and clears it.
 * @return          A new protocol.
 */
#define InitializeProtocol(name,start,stop,encode,decode,flush,state) { .Name = name, .Start = start, .Stop = stop, .Encode = encode, .Decode = decode, .Flush = flush, .State = state }

#endif
