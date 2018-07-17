
#ifndef PROTOCOLMANAGER_H
#define PROTOCOLMANAGER_H

#include "DataStream.h"
#include <stdint.h>

#define PROTOCOLEXITCODE_LENGTH 5
#define IDENTIFIER_EXITCHUNK "EXIT"

uint8_t InitiateProtocol (char protocol []);
uint8_t TerminateProtocol (char exitcode []);

uint8_t WriteStream (ChunkCollection input);
uint8_t ReadStream (DataStream output);

DataStream GetTransmissionMatrix (void);
ChunkCollection GetReceptionMatrix (void);

#endif
