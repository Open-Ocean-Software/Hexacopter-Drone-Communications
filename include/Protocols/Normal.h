
#ifndef PROTOCOL_NORMAL_H
#define PROTOCOL_NORMAL_H

#define PROTOCOL_NORMAL_NAME "NORM"
#define PROTOCOL_NORMAL_START &Protocol_Normal_Start
#define PROTOCOL_NORMAL_STOP &Protocol_Normal_Stop
#define PROTOCOL_NORMAL_ENCODE &Protocol_Normal_Encode
#define PROTOCOL_NORMAL_DECODE &Protocol_Normal_Decode
#define PROTOCOL_NORMAL_FLUSH &Protocol_Normal_Flush
#define PROTOCOL_NORMAL_STATE &Protocol_Normal_State

void Protocol_Normal_Start (void);
void Protocol_Normal_Stop (void);
void Protocol_Normal_Encode (ChunkCollection chunks);
void Protocol_Normal_Decode (DataStream stream);
DataStream Protocol_Normal_Flush (void);
ChunkCollection Protocol_Normal_State (void);

#define NORM_ERRORPHRASE "\xFFERR\xFF"
#define NORM_ERRORPHRASE_LENGTH 5

#define NORM_INITPHRASE "NORM\x88NORMAL\x81\rEND\xFF"
#define NORM_INITPHRASE_LENGTH 17

#define NORM_CLOSEPHRASE "\x88NORMAL\x81\rSTOP\xFF"
#define NORM_CLOSEPHRASE_LENGTH 5

#define NORM_STARTPHRASE "\x88NORMAL\x81\r"
#define NORM_STARTPHRASE_LENGTH 9
#define NORM_HEADPHRASE "HEAD\r"
#define NORM_HEADPHRASE_LENGTH 5
#define NORM_BODYPHRASE "BODY\r"
#define NORM_BODYPHRASE_LENGTH 5
#define NORM_ENDPHRASE "END\xFF"
#define NORM_ENDPHRASE_LENGTH 4

#define NORM_ENDCHUNKPHRASE { '\0', '\0', '\0' }
#define NORM_ENDCHUNKPHRASE_LENGTH 3

#endif
