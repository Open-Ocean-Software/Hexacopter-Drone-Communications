
#ifndef PROTOCOLMANAGER_H
#define PROTOCOLMANAGER_H

#include "DataStream.h"
#include <stdint.h>

#define PROTOCOLEXITCODE_LENGTH 5
#define IDENTIFIER_EXITCHUNK "EXIT"

/**
 * Initiates the start of one protocol.
 * @param  protocol The name of the selected protocol
 * @return          Success code
 */
uint8_t InitiateProtocol (char protocol []);
/**
 * Terminates the current protocol.
 * @param  exitcode The termination exit code
 * @return          Success code
 */
uint8_t TerminateProtocol (char exitcode []);

/**
 * Recompiles the chunks given the specified protocol.
 * @param  input The chunks to compile
 * @return       Success code
 */
uint8_t WriteStream (ChunkCollection input);
/**
 * Decompiles the chunks given the specified protocol.
 * @param  output The stream to decompile
 * @return        Success code
 */
uint8_t ReadStream (DataStream output);

/**
 * Gets the fully compiled transmission matrix.
 * @return  The transmission matrix data stream
 */
DataStream GetTransmissionMatrix (void);
/**
 * Gets the fully decompiled and updated reception matrix.
 * @return  The reception matrix chunk collection
 */
ChunkCollection GetReceptionMatrix (void);

#endif
