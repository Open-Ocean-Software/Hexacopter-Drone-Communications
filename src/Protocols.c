
#include "Protocols.h"

Protocol Protocols [PROTOCOL_LIST_COUNT] = { PROTOCOL_LIST };

Protocol *FindProtocol (char name[])
{
    Protocol *protocol;
    TryFindProtocol(name, protocol);
    return protocol;
}

uint8_t TryFindProtocol (char name[], Protocol *protocol)
{
    for (int i = 0; i < PROTOCOL_LIST_COUNT; i++) {
        uint8_t match = 0x1;
        for (int j = 0; j < PROTOCOLNAME_LENGTH; j++) {
            match &= (name[j] == Protocols[i].Name[j]);
        }
        if (match) {
            protocol = &(Protocols[i]);
            return 0x1;
        }
    }
    return 0x0;
}

uint8_t ProtocolExists (char name[])
{
    Protocol *protocol;
    return TryFindProtocol(name, protocol);
}
