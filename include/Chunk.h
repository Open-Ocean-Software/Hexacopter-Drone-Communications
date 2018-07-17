
#ifndef CHUNK_H
#define CHUNK_H

#define CHUNKIDENTIFIER_LENGTH 4

typedef struct {
    char Identifier [CHUNKIDENTIFIER_LENGTH];
    DataStream Data;
} Chunk;

/**
 * Creates a new chunk of data.
 * @param  identifier The chunk identifier.
 * @param  data       The chunk data.
 * @return            A new chunk.
 */
#define InitializeChunk(identifier,data) { .Identifier = identifier, .Data = data }

#endif
