
#include "TWIMasterManager.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void InitializeTWIMaster (void)
{
    // Clear the status register
    TWSR0 = 0x00;
    // Set the bit rate register
    TWBR0 = ((F_CPU / TWI_FREQ) - 16) / 2;
    // Enable the TWI module with the interrupt
    TWCR0 = (1 << TWIE) | (1 << TWEN);
    // Clear the data register
    TWDR0 = 0x00;
}

volatile TWIErrorCode twiError = None;
volatile TWIActionCode twiAction = None;
volatile TWIStatusCode twiStatus = None;

void (*intHandler)(void) = 0;

TWIStatusCode GetTWIStatusCode (void)
{
    return twiStatus;
}
TWIActionCode GetTWIActionCode (void)
{
    return twiAction;
}
TWIErrorCode GetTWIErrorCode (void)
{
    return twiError;
}
void ClearTWIErrorCode (void)
{
    twiError = None;
}

uint8_t TransmitByteTWI (uint8_t addr, uint8_t data)
{
    return transmitBytesTWI(addr, &data, 1);
}
uint8_t TransmitTWI (uint8_t addr, uint8_t *data, size_t length)
{
    return transmitBytesTWI(addr, data, length);
}

uint8_t ReceiveByteTWI (uint8_t addr, uint8_t *data)
{
    return receiveBytesTWI(addr, data, 1);
}
uint8_t ReceiveTWI (uint8_t addr, uint8_t *data, size_t length)
{
    return receiveBytesTWI(addr, data, length);
}

void CloseTWI (void)
{
    TWSR0 = 0x00;
    TWDR0 = 0x00;
    TWCR0 = 0x00;
    twiError = None;
    twiAction = None;
    twiStatus = None;
}




uint8_t transmitBytesTWI (uint8_t addr, uint8_t *data, size_t length)
{
    if ((addr & 0x7F) == 0x00) {
        twiError = Error;
        return 0x0;
    }
    if (!sendTWIStartCondition()) {
        twiError = StartFailed;
        return 0x0;
    }
    if (!sendTWISlaW(addr)) {
        twiError = SlaWFailed;
        return 0x0;
    }
    for (int i = 0; i < length; i++) {
        if (!sendTWIData(data[i])) {
            twiError = DataFailed;
            return 0x0;
        }
    }
    if (!sendTWIStopCondition()) {
        twiError = StopFailed;
        return 0x0;
    }

    twiError = None;
    return 0x1;
}

uint8_t receiveBytesTWI (uint8_t addr, uint8_t *data, size_t length)
{
    if ((addr & 0x7F) == 0x00) {
        twiError = Error;
        return 0x0;
    }
    if (!sendTWIStartCondition()) {
        twiError = StartFailed;
        return 0x0;
    }
    if (!sendTWISlaR(addr)) {
        twiError = SlaRFailed;
        return 0x0;
    }
    for (int i = 0; i < length; i++) {
        if (!receiveTWIData(&(data[i]), i + 1 == length)) {
            twiError = DataFailed;
            return 0x0;
        }
    }
    if (!sendTWIStopCondition()) {
        twiError = StopFailed;
        return 0x0;
    }

    twiError = None;
    return 0x1;
}


uint8_t sendTWIStartCondition (void)
{
    // Send the start condition and clear the interrupt
    twiActivate(Starting);
    TWCR0 = (1 << TWIE) | (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
    while (!twiContinue()) ;
    if (!twiMatches(StartSent)) {
        return 0x0;
    }
    return 0x1;
}
uint8_t sendTWIStopCondition (void)
{
    // Send the stop condition and clear the interrupt
    TWCR0 = (1 << TWIE) | (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
    return 0x1;
}

uint8_t sendTWISlaW (uint8_t addr)
{
    // Set SLA+W write bit
    addr &= 0x80
    // Send the SLA+W and clear the interrupt
    twiActivate(MTSlaW);
    sendTWIAddr(addr);
    if (!twiMatches(MTSlaWAck)) {
        return 0x0;
    }
    return 0x1;
}
uint8_t sendTWISlaR (uint8_t addr)
{
    // Set SLA+R read bit
    addr |= 0x80;
    // Send the SLA+R and clear the interrupt
    twiActivate(MRSlaR);
    sendTWIAddr(addr);
    if (!twiMatches(MTSlaRAck)) {
        return 0x0;
    }
    return 0x1;
}
void sendTWIAddr (uint8_t addr)
{
    TWDR0 = addr;
    TWCR0 = (1 << TWIE) | (1 << TWEN) | (1 << TWINT);
    while (!twiContinue()) ;
}

uint8_t sendTWIData (uint8_t data)
{
    // Send data and clear the interrupt
    twiActivate(MTData);
    TWDR0 = data;
    TWCR0 = (1 << TWIE) | (1 << TWEN) | (1 << TWINT);
    while (!twiContinue()) ;
    if (!twiMatches(MTData)) {
        return 0x0;
    }
    return 0x1;
}
uint8_t receiveTWIData (uint8_t *data, uint8_t isLast)
{
    twiActivate(MRData);
    TWCR0 = (1 << TWIE) | (1 << TWEN) | (1 << TWINT);
    if (isLast) {
        TWCR0 &= ~(1 << TWEA);
    } else {
        TWCR0 |= (1 << TWEA);
    }
    while (!twiContinue()) ;
    if (!twiMatches(MRData)) {
        return 0x0;
    }
    *data = TWDR0;
    return 0x1;
}


uint8_t twiActivate (TWIActionCode action)
{
    twiAction = action;
}
uint8_t twiContinue (void)
{
    return twiAction == None;
}

uint8_t twiMatches (TWIStatusCode code)
{
    return ((twiStatus == code) && twiContinue());
}

void SetTWIInterruptHandler (void (*handler)(void))
{
    intHandler = handler;
}

void UnsetTWIInterruptHandler (void)
{
    intHandler = 0;
}

ISR (TWI_vect)
{
    twiStatus = GetTWIStatusCode();
    twiAction = None;
    switch (twiStatus) {
        case MTSlaWNAck:
        case MTDataNAck:
        case MRSlaRNAck:
        case MRDataNAck:
            twiError = Error;
            break;
        case ArbitrationLost:
            twiError = LostArbitration;
            break;
        case MTDataAck:
        case MRDataAck:
            if (intHandler != 0) {
                intHandler();
            }
            break;
        default:
            twiError = None;
            break;
    }
}
