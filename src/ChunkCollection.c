
#include "ChunkCollection.h"
#include "Chunk.h"

uint8_t compareIdentifiers (char *a, char *b)
{
    uint8_t same = 0x1;
    for (int i = 0; i < CHUNKIDENTIFIER_LENGTH; i++) {
        same &= (a[i] == b[i]);
    }
    return same;
}

uint8_t identifierHasMatch (ChunkCollection chunks, char *id)
{
    uint8_t hasMatch = 0x0;
    for (int i = 0; i < chunks.Count; i++) {
        hasMatch |= compareIdentifiers(chunks.Items[i].Identifier, id);
    }
    return hasMatch;
}

ChunkCollection UnionChunkCollection (ChunkCollection base, ChunkCollection addition)
{
    int size = addition.Count;
    for (int i = 0; i < base.Count; i++) {
        if (!identifierHasMatch(addition, base.Items[i].Identifier)) {
            size++;
        }
    }
    Chunk chunks [size];
    int additionSize = sizeof(Chunk) * addition.Count;
    memcpy(chunks, addition.Data, additionSize);
    int pos = additionSize;
    for (int i = 0; i < base.Count; i++) {
        if (!identifierHasMatch(addition, base.Items[i].Identifier)) {
            pos = additionSize + (i * sizeof(Chunk));
            memcpy(chunks + pos, &(base.Items[i]), sizeof(Chunk));
        }
    }
    ChunkCollection collection = InitializeChunkCollection(chunks, size);
    return collection;
}
