
#include "ProtocolManager.h"
#include "DataStream.h"

Protocol *currentProtocol = 0;

uint8_t InitiateProtocol (char protocol[])
{
    uint8_t success = TryFindProtocol(protocol, currentProtocol);
    if (success) {
        currentProtocol->Start();
    }
    return success;
}

uint8_t TerminateProtocol (char exitcode [])
{
    if (currentProtocol != 0) {
        uint8_t exitData [PROTOCOLEXITCODE_LENGTH];
        memcpy(exitData, exitcode, PROTOCOLEXITCODE_LENGTH * sizeof(uint8_t));
        DataStream exitStream = InitializeDataStream(exitData, PROTOCOLEXITCODE_LENGTH);
        char exitChunkIdentifier[] = IDENTIFIER_EXITCHUNK;
        Chunk exitChunk = InitializeChunk(exitChunkIdentifier, exitStream);
        Chunk exitChunksData [] = { exitChunk };
        ChunkCollection exitChunks = InitializeChunkCollection(exitChunksData, 1);

        currentProtocol->Encode(exitChunks);
        currentProtocol->Stop();
        return 0x1;
    }
    return 0x0;
}

uint8_t WriteStream (ChunkCollection input)
{
    if (currentProtocol != 0) {
        currentProtocol->Encode(input);
        return 0x1;
    }
    return 0x0;
}

uint8_t ReadStream (DataStream output)
{
    if (currentProtocol != 0) {
        currentProtocol->Decode(output);
        return 0x1;
    }
    return 0x0;
}

DataStream GetTransmissionMatrix (void)
{
    if (currentProtocol != 0) {
        return currentProtocol->Flush();
    }
    return 0;
}

ChunkCollection GetReceptionMatrix (void)
{
    if (currentProtocol != 0) {
        return currentProtocol->State();
    }
    return 0;
}
