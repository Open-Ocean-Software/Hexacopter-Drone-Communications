
#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include "Protocol.h"
#include <stdint.h>

///////////////////////
// Include Protocols //
///////////////////////
#include "Protocols/Minimal.h"
#include "Protocols/Restricted.h"
#include "Protocols/Normal.h"
#include "Protocols/Video.h"
#include "Protocols/Universal.h"

////////////////////////
// Register Protocols //
////////////////////////
#define PROTOCOL_LIST       InitializeProtocol(PROTOCOL_NORMAL_NAME, PROTOCOL_NORMAL_START, PROTOCOL_NORMAL_STOP, PROTOCOL_NORMAL_ENCODE, PROTOCOL_NORMAL_DECODE, PROTOCOL_NORMAL_FLUSH, PROTOCOL_NORMAL_STATE)

#define PROTOCOL_LIST_COUNT 1


extern Protocol Protocols [];

Protocol *FindProtocol (char name[]);
uint8_t TryFindProtocol (char name[], Protocol *protocol);
uint8_t ProtocolExists (char name[]);

#endif
