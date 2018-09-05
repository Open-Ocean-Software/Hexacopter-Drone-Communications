
#ifndef TWIMANAGER_H
#define TWIMANAGER_H

#define TWI_FREQ 100000

#define TWI_TWSR_STATUSMASK 0xF8

#define GetTWIStatusCode() (TWIStatusCode)(TWSR0 & TWI_TWSR_STATUSMASK)

typedef enum {
    None = 0x00,
    StartSent = 0x08,
    RepStartSent = 0x10,
    MTSlaWAck = 0x18,
    MTSlaWNAck = 0x20,
    MTDataAck = 0x28,
    MTDataNAck = 0x30,
    ArbitrationLost = 0x38,
    MRSlaRAck = 0x40,
    MRSlaRNAck = 0x48,
    MRDataAck = 0x50,
    MRDataNAck = 0x58,
} TWIStatusCode;

typedef enum {
    None,
    Starting,
    Repeating,
    MTSlaW,
    MTData,
    MRSlaR,
    MRData
} TWIActionCode;

typedef enum {
    None,
    Error,
    LostArbitration,
    StartFailed,
    SlaWFailed,
    SlaRFailed,
    DataFailed,
    StopFailed
} TWIErrorCode;

void InitializeTWIMaster (void);

TWIStatusCode GetTWIStatusCode (void);
TWIActionCode GetTWIActionCode (void);
TWIErrorCode GetTWIErrorCode (void);
void ClearTWIErrorCode (void);


uint8_t TransmitByteTWI (uint8_t addr, uint8_t data);
uint8_t TransmitTWI (uint8_t addr, uint8_t *data, size_t length);
uint8_t ReceiveByteTWI (uint8_t addr, uint8_t *data);
uint8_t ReceiveTWI (uint8_t addr, uint8_t *data, size_t length);

void SetTWIInterruptHandler (void (*handler)(void));
void UnsetTWIInterruptHandler (void);

void CloseTWI (void);

#endif
