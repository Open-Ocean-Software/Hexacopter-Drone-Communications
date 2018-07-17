
#include "Helpers/CheckSumHelper.h"

DataStream GenerateCheckSumStream (DataStream input)
{
    int wordCount = (input.Count / 2) + (input.Count % 2);
    uint16_t words [wordCount];
    memcpy(words, input.Data, input.Count * sizeof(uint8_t));

    uint16_t checkSum = words[0];
    for (int i = 1; i < wordCount; i++) {
        checkSum ^= words[i];
    }

    uint8_t checkSumData [sizeof(uint16_t)];
    memcpy(checkSumData, &checkSum, sizeof(uint16_t));
    DataStream csStream = InitializeDataStream(checkSumData, sizeof(uint16_t));
    return csStream;
}

uint8_t VerifyCheckSumStream (DataStream stream, DataStream cs)
{
    int streamWordCount = (stream.Count / 2) + (input.Count % 2);
    int csWordCount = (cs.Count / 2) + (cs.Count % 2);
    int wordCount = streamWordCount + csWordCount;

    uint16_t words [wordCount];
    memcpy(words, stream.Data, input.Count * sizeof(uint8_t));
    int csPosition = wordCount - csWordCount;
    memcpy(words + csPosition, cs.Data, cs.Count * sizeof(uint8_t));

    uint16_t result = words[0];
    for (int i = 1; i < wordCount; i++) {
        result ^= words[i];
    }

    return (result == 0x0000);
}
