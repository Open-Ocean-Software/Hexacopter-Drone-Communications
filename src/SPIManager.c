
#include "SPIManager.h"
#include <avr/interrupt.h>
#include <avr/io.h>

SPIRole spiRole = None;
void (*intHandler)(uint8_t data) = 0;

void InitializeSPIMaster (void)
{
    DDRB |= (1 << PB3) | (1 << PB5);
    DDRB &= ~(1 << PB4);
    SPCR0 = (1 << SPE0) | (1 << MSTR0) | (1 << SPR00) | (1 << SPIE0);
    SPDR0 = 0x00;
    sei();
    spiRole = Master;
}

void InitializeSPISlave (void)
{
    DDRB |= (1 << PB4);
    DDRB &= ~((1 << PB5) | (1 << PB3) | (1 << PB2));
    SPCR0 = (1 << SPE0) | (1 << SPIE0);
    SPDR0 = 0x00;
    sei();
    spiRole = Slave;
}

void TransmitSPI (uint8_t *data, int length)
{
    for (int i = 0; i < length; i++) {
        TransmitByteSPI(data[i]);
    }
}

void TransmitByteSPI (uint8_t data)
{
    uint8_t temp;
    TransceiveByteSPI(data, &temp);
}

void ReceiveSPI (uint8_t *data, int length)
{
    for (int i = 0; i < length; i++) {
        ReceiveByteSPI(&(data[i]));
    }
}

void ReceiveByteSPI (uint8_t *data)
{
    TransceiveByteSPI(0x00, data);
}

void TransceiveSPI (uint8_t *transmit, uint8_t *receive, int length)
{
    for (int i = 0; i < length; i++) {
        TransceiveByteSPI(transmit[i], &(receive[i]));
    }
}

void TransceiveByteSPI (uint8_t transmit, uint8_t *receive)
{
    SPDR0 = transmit;
    while (!(SPSR0 & (1 << SPIF0))) ;
    *receive = SPDR0;
}

uint8_t SelectSPISSEnabler (volatile uint8_t *ddr, volatile uint8_t *port, uint8_t mask)
{
    if (spiRole != Master) {
        return 0x0;
    }

    static volatile uint8_t *oldDDR = 0;
    static volatile uint8_t *oldPort = 0;
    static uint8_t oldMask = 0x00;

    if (ddr != oldDDR || port != oldPort || mask != oldMask) {
        *oldDDR &= ~mask;
        *oldPort &= ~mask;
    }

    *ddr |= mask;
    *port |= mask;

    oldDDR = ddr;
    oldPort = port;
    oldMask = mask;

    return 0x1;
}

void SetSPIInterruptHandler (void (*handler)(uint8_t data))
{
    intHandler = handler;
}

void UnsetSPIInterruptHandler (void)
{
    intHandler = 0;
}

void CloseSPI (void)
{
    SPCR0 = 0x00;
    SPDR = 0x00;
}

ISR(SPI_STC_vect)
{
    if (intHandler != 0) {
        while (!(SPSR0 & (1 << SPIF0))) ;
        uint8_t data = SPDR0;
        intHandler(data);
    }
}
