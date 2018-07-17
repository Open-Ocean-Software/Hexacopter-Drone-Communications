
#include "Protocols/Normal.h"
#include "CompressionManager.h"
#include "EncryptionManager.h"
#include "Helpers/CheckSumHelper.h"
#include "DataStream.h"
#include "Chunk.h"
#include "ChunkCollection.h"


void Protocol_Normal_Start (void)
{
    Protocol_Normal_Flush();
    char startMessage[] = NORM_INITPHRASE;
    if (writeDataIfNotActive(startMessage, NORM_INITPHRASE_LENGTH)) {
        streamActive = 0x1;
    } else {
        streamActive = 0x0;
    }
}

void Protocol_Normal_Stop (void)
{
    char stopMessage[] = NORM_CLOSEPHRASE;
    writeDataIfActive(startMessage, NORM_CLOSEPHRASE_LENGTH)
    streamActive = 0x0;
}

void Protocol_Normal_Encode (ChunkCollection chunks)
{
    encodingImageMatrix = UnionChunkCollection(encodingImageMatrix, chunks);
}

void Protocol_Normal_Decode (DataStream stream)
{
    decompileChunks(stream);
}

DataStream Protocol_Normal_Flush (void)
{
    if (streamActive) {
        DataStream messageStream = compileChunks(encodingImageMatrix);
        currentStream = AppendStream(currentStream, messageStream);
    }
    DataStream flushed = currentStream;
    currentStream = InitializeDataStream(0, 0);
    return flushed;
}

ChunkCollection Protocol_Normal_State (void)
{
    ChunkCollection stateMatrix = decodingImageMatrix;
    decodingImageMatrix = InitializeChunkCollection(0, 0);
    return stateMatrix;
}



DataStream currentStream = InitializeDataStream(0, 0);
ChunkCollection encodingImageMatrix = InitializeChunkCollection(0, 0);
ChunkCollection decodingImageMatrix = InitializeChunkCollection(0, 0);
uint8_t streamActive = 0x0;

const int identifierSize = sizeof(char) * CHUNKIDENTIFIER_LENGTH;
const int locationSize = sizeof(int);
const int sizeSize = sizeof(int);
const int headChunkLength = identifierSize + locationSize + sizeSize;
const int csStreamLength = CHECKSUMSTREAMLENGTH;
const int headLineLength = identifierSize + locationSize + sizeSize + csStreamLength;


DataStream convertToDataStream (char *message, int msgLength)
{
    int streamSize = sizeof(uint8_t) * msgLength;
    uint8_t data [streamSize];
    memcpy(data, message, streamSize);
    DataStream stream = InitializeDataStream(data, msgLength);
    return stream;
}

void writeDataToStream (char *message, int msgLength)
{
    DataStream stream = convertToDataStream(message, msgLength);
    currentStream = AppendStream(currentStream, stream);
}

void writeErrorData (void)
{
    char errorMessage[] = NORM_ERRORPHRASE;
    writeDataIfActive(errorMessage, NORM_ERRORPHRASE_LENGTH);
    streamActive = 0x0;
}

uint8_t writeDataIf (char *message, int msgLength, uint8_t mask)
{
    if (streamActive & mask == mask) {
        writeDataToStream(message, msgLength);
        return 0x1;
    } else {
        writeErrorData();
        return 0x0;
    }
}

uint8_t writeDataIfActive (char *message, int msgLength)
{
    return writeDataIf(message, msgLength, 0x1);
}

uint8_t writeDataIfNotActive (char *message, int msgLength)
{
    return writeDataIf(message, msgLength, 0x0);
}

uint8_t phraseExists (DataStream stream, char *phrase, int location, int length)
{
    if (stream.Length < location + length) {
        return 0x0;
    }
    uint8_t same = 0x1;
    for (int i = location; i < location + length; i++) {
        same &= (phrase[i] == stream.Data[i]);
    }
    return same;
}

int phraseFindNextOccurrence (DataStream stream, char *phrase, int start, int end, int length)
{
    if (start < 0 || end < 1 || length < 1) {
        return -1;
    }
    if (end <= start || start + length > end) {
        return -1;
    }
    if (stream.Length < start + length || stream.Length < end) {
        return -1;
    }
    for (int i = start; i < start + end - length; i++) {
        for (int j = 0; j < length; j++) {
            if (stream.Data[i + j] != phrase[j]) {
                break;
            }
            if (j == length - 1) {
                return i;
            }
        }
    }
    return -1;
}

ChunkCollection parseChunksFromStreams (DataStream head, DataStream body)
{
    int chunkCount = head.Length / headLineLength;
    Chunk chunkData [chunkCount];
    ChunkCollection instanceMatrix = InitializeChunkCollection(chunkData, chunkCount);

    char chunkIdentifier [CHUNKIDENTIFIER_LENGTH];
    int location;
    int size;
    uint8_t csData [CHECKSUMSTREAMLENGTH];
    DataStream cs;
    DataStream data;

    for (int i = 0; i < chunkCount; i++) {
        int loc = i * headLineLength;
        memcpy(chunkIdentifier, head.Data + loc, identifierSize);
        loc += identifierSize;
        memcpy(&location, head.Data + loc, locationSize);
        loc += locationSize;
        memcpy(&size, head.Data + loc, sizeSize);
        loc += sizeSize;
        memcpy(csData, head.Data + loc, CHECKSUMSTREAMLENGTH);
        cs = InitializeDataStream(csData, CHECKSUMSTREAMLENGTH);
        uint8_t dataData [size];
        memcpy(dataData, body.Data, size);
        data = InitializeDataStream(dataData, size);
        if (VerifyCheckSumStream(data, cs) && VerifyCrypt(data)) {
            Decrypt(data, &data);
            Decompress(data, &data);
            Chunk chunk = InitializeChunk(chunkIdentifier, data);
            instanceMatrix.Items[i] = chunk;
        }
    }
    return instanceMatrix;
}

ChunkCollection decompileChunks (DataStream message)
{
    int loc = 0;
    while (loc < message.Length) {
        char phrase[] = NORM_ERRORPHRASE;
        if (phraseExists(message, phrase, loc, NORM_ERRORPHRASE_LENGTH)) {
            decodingImageMatrix = InitializeChunkCollection(0, 0);
            streamActive = 0x0;
            break;
        }
        phrase = NORM_INITPHRASE;
        if (phraseExists(message, phrase, loc, NORM_INITPHRASE_LENGTH)) {
            decodingImageMatrix = InitializeChunkCollection(0, 0);
            break;
        }
        phrase = NORM_CLOSEPHRASE;
        if (phraseExists(message, phrase, loc, NORM_CLOSEPHRASE_LENGTH)) {
            streamActive = 0x0;
            break;
        }

        phrase = NORM_STARTPHRASE;
        if (phraseExists(message, phrase, loc, NORM_STARTPHRASE_LENGTH)) {
            loc += NORM_STARTPHRASE_LENGTH;
            phrase = NORM_HEADPHRASE;
            if (phraseExists(message, phrase, loc, NORM_HEADPHRASE_LENGTH)) {
                loc += NORM_HEADPHRASE_LENGTH;
                phrase = NORM_ENDCHUNKPHRASE;
                int chunkEnd = phraseFindNextOccurrence(message, phrase, loc, message.Length - 1, NORM_ENDCHUNKPHRASE_LENGTH);
                if (chunkEnd != -1) {
                    uint8_t headData [chunkEnd - loc];
                    memcpy(headData, message.Data + loc, chunkEnd - loc);
                    DataStream head = InitializeDataStream(headData, chunkEnd - loc);
                    Decrypt(head, &head);

                    if (head.Length % headLineLength == 0) {
                        loc = chunkEnd + NORM_ENDCHUNKPHRASE_LENGTH;
                        phrase = NORM_BODYPHRASE;
                        if (phraseExists(message, phrase, loc, NORM_BODYPHRASE_LENGTH)) {
                            loc += NORM_BODYPHRASE_LENGTH;
                            phrase = NORM_ENDCHUNKPHRASE;
                            chunkEnd = phraseFindNextOccurrence(message, phrase, loc, message.Length - 1, NORM_ENDCHUNKPHRASE_LENGTH);
                            if (chunkEnd != -1) {
                                uint8_t bodyData [chunkEnd - loc];
                                memcpy(bodyData, message.Data + loc, chunkEnd - loc);
                                DataStream body = InitializeDataStream(bodyData, chunkEnd - loc);

                                loc = chunkEnd + NORM_ENDCHUNKPHRASE_LENGTH;
                                phrase = NORM_ENDPHRASE;
                                if (phraseExists(message, phrase, loc, NORM_ENDPHRASE_LENGTH)) {
                                    ChunkCollection instanceMatrix = parseChunksFromStreams(head, body);
                                    decodingImageMatrix = UnionChunkCollection(decodingImageMatrix, instanceMatrix);
                                    loc += NORM_ENDPHRASE_LENGTH;
                                    continue;
                                }
                            }
                        }
                    }
                }
            }
        }
        writeErrorData();
        decodingImageMatrix = InitializeChunkCollection(0, 0);
        break;
    }
    return decodingImageMatrix;
}

DataStream compileChunks (ChunkCollection imageMatrix)
{
    char message[] = NORM_STARTPHRASE;
    if (writeDataIfActive(message, NORM_STARTPHRASE_LENGTH)) {
        char identifier [CHUNKIDENTIFIER_LENGTH];
        DataStream data;
        int size;
        int location = 0;
        uint8_t headChunkData [headChunkLength];
        DataStream headChunkTemp;
        DataStream csStream;
        DataStream head = InitializeDataStream(0, 0);
        DataStream body = InitializeDataStream(0, 0);
        for (int i = 0; i < imageMatrix.Count; i++) {
            identifier = imageMatrix.Items[i].Identifier;
            data = imageMatrix.Items[i].Data;
            Compress(data, &data);
            Encrypt(data, &data);
            size = data.Length;
            memcpy(headChunkData, identifier, identifierSize);
            memcpy(headChunkData + identifierSize, &location, locationSize);
            memcpy(headChunkData + identifierSize + locationSize, &size, sizeSize);
            headChunkTemp = InitializeDataStream(headChunkData, headChunkLength);
            csStream = GenerateCheckSumStream(data);
            headChunkTemp = AppendStream(headChunkTemp, csStream);
            head = AppendStream(head, headChunkTemp);
            body = AppendStream(body, data);
            location += size;
        }
        Encrypt(head, &head);

        message = NORM_HEADPHRASE;
        writeDataToStream(message, NORM_HEADPHRASE_LENGTH);
        currentStream = AppendStream(currentStream, head);
        message = NORM_ENDCHUNKPHRASE;
        writeDataToStream(message, NORM_ENDCHUNKPHRASE_LENGTH);
        message = NORM_BODYPHRASE;
        writeDataToStream(message, NORM_BODYPHRASE);
        currentStream = AppendStream(currentStream, body);
        message = NORM_ENDCHUNKPHRASE;
        writeDataToStream(message, NORM_ENDCHUNKPHRASE_LENGTH);
        message = NORM_ENDPHRASE;
        writeDataToStream(message, NORM_ENDPHRASE_LENGTH);
    }
    return currentStream;
}
