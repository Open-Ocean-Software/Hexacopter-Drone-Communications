
#ifndef SPIMANAGER_H
#define SPIMANAGER_H

typedef enum {
    None,
    Master,
    Slave
} SPIRole;

/**
 * Initializes the SPI module as a master.
 */
void InitializeSPIMaster (void);
/**
 * Initializes the SPI module as a slave.
 */
void InitializeSPISlave (void);

/**
 * Transmits a string of data via SPI.
 * @param data   The payload string
 * @param length The length of the payload
 */
void TransmitSPI (uint8_t *data, int length);
/**
 * Transmits one byte of data via SPI.
 * @param data The payload byte
 */
void TransmitByteSPI (uint8_t data);
/**
 * Receives a string of data via SPI.
 * @param data   The payload string
 * @param length The length of the payload
 */
void ReceiveSPI (uint8_t *data, int length);
/**
 * Receives one byte of data via SPI.
 * @param data The payload byte
 */
void ReceiveByteSPI (uint8_t *data);
/**
 * Transceives a string of data via SPI.
 * @param transmit The transmit payload string
 * @param receive  The reception payload string
 * @param length   The length of the payloads
 */
void TransceiveSPI (uint8_t *transmit, uint8_t *receive, int length);
/**
 * Transceives one byte of data via SPI.
 * @param transmit The transmit payload byte
 * @param receive  The reception payload byte
 */
void TransceiveByteSPI (uint8_t transmit, uint8_t *receive);

/**
 * Sets the SPI Slave Select (SS).
 * @param  ddr  The data direction register
 * @param  port The port
 * @param  mask The mask
 * @return      Success code
 */
uint8_t SelectSPISSEnabler (volatile uint8_t *ddr, volatile uint8_t *port, uint8_t mask);

/**
 * Sets the SPI interrupt handler.
 * @param handler The handler function pointer
 */
void SetSPIInterruptHandler (void (*handler)(uint8_t data));
/**
 * Unsets the SPI interrupt handler.
 */
void UnsetSPIInterruptHandler (void);

/**
 * Stops the SPI module.
 */
void CloseSPI (void);

#endif
