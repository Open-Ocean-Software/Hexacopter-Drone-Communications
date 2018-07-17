
#ifndef CHUNKCOLLECTION_H
#define CHUNKCOLLECTION_H

typedef struct {
    Chunk Items [];
    int Count;
} ChunkCollection;

/**
 * Creates a new chunk collection.
 * @param  items The chunk items.
 * @param  count The amount of chunks.
 * @return       A new chunk collection.
 */
#define InitializeChunkCollection(items,count) { .Items = items, .Count = count }

/**
 * Unions two chunk collections.
 * @param  base     The first chunk collection.
 * @param  addition The second chunk collection.
 * @return          The unioned chunk collection.
 */
ChunkCollection UnionChunkCollection (ChunkCollection base, ChunkCollection addition);

#endif
