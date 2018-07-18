
#ifndef SPIMANAGER_H
#define SPIMANAGER_H

typedef enum {
    None,
    Master,
    Slave
} SPIRole;

void InitializeSPIMaster (void);
void InitializeSPISlave (void);

void TransmitSPI (uint8_t *data, int length);
void TransmitByteSPI (uint8_t data);
void ReceiveSPI (uint8_t *data, int length);
void ReceiveByteSPI (uint8_t *data);
void TransceiveSPI (uint8_t *transmit, uint8_t *receive, int length);
void TransceiveByteSPI (uint8_t transmit, uint8_t *receive);

uint8_t SelectSPISSEnabler (volatile uint8_t *ddr, volatile uint8_t *port, uint8_t mask);

void SetSPIInterruptHandler (void (*handler)(uint8_t data));
void UnsetSPIInterruptHandler (void);

void CloseSPI (void);

#endif
