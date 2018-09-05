
#ifndef TWIMANAGER_H
#define TWIMANAGER_H

#define TWI_FREQ 100000

#define TWI_TWSR_STATUSMASK 0xF8

/**
 * Gets the current TWI status code.
 * @return The status code
 */
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

/**
 * Initializes the TWI module as a master.
 */
void InitializeTWIMaster (void);

/**
 * Gets the current TWI status code.
 * @return  The status code
 */
TWIStatusCode GetTWIStatusCode (void);
/**
 * Gets the current TWI action code.
 * @return  The action code
 */
TWIActionCode GetTWIActionCode (void);
/**
 * Gets the current TWI error code.
 * @return  The error code
 */
TWIErrorCode GetTWIErrorCode (void);
/**
 * Clears the TWI error code.
 */
void ClearTWIErrorCode (void);

/**
 * Transmits one byte via TWI.
 * @param  addr The address of the slave
 * @param  data The payload byte
 * @return      Success code
 */
uint8_t TransmitByteTWI (uint8_t addr, uint8_t data);
/**
 * Transmits a string of data via TWI.
 * @param  addr   The address of the slave
 * @param  data   The payload string
 * @param  length The length of the payload
 * @return        Success code
 */
uint8_t TransmitTWI (uint8_t addr, uint8_t *data, size_t length);
/**
 * Receives one byte via TWI.
 * @param  addr The address of the slave
 * @param  data The payload byte
 * @return      Success code
 */
uint8_t ReceiveByteTWI (uint8_t addr, uint8_t *data);
/**
 * Receives a string of data via TWI.
 * @param  addr   The address of the slave
 * @param  data   The payload string
 * @param  length The length of the payload
 * @return        Success code
 */
uint8_t ReceiveTWI (uint8_t addr, uint8_t *data, size_t length);

/**
 * Sets the TWI interrupt handler.
 * @param handler The handler function pointer
 */
void SetTWIInterruptHandler (void (*handler)(void));
/**
 * Unsets the TWI interrupt handler.
 */
void UnsetTWIInterruptHandler (void);

/**
 * Closes the TWI module.
 */
void CloseTWI (void);

#endif
