
#ifndef USARTMANAGER_H
#define USARTMANAGER_H

#define USART_DEFAULT_BAUD 9600

/**
 * Initializes the USART module with the default BAUD.
 */
void InitializeUSART (void);
/**
 * Initializes the USART module with a custom BAUD.
 * @param ubbr The custom BAUD rate
 */
void InitializeUSARTWithBAUD (unsigned int ubbr);

/**
 * Transmits a string of data via USART.
 * @param data   The payload string
 * @param length The length of the payload
 */
void TransmitUSART (uint8_t *data, int length);
/**
 * Transmits one byte of data via USART.
 * @param data The payload byte
 */
void TransmitByteUSART (uint8_t data);
/**
 * Receives a string of data via USART.
 * @param data   The payload string
 * @param length The length of the payload
 */
void ReceiveUSART (uint8_t *data, int length);
/**
 * Receives one byte of data via USART.
 * @param data The payload byte
 */
void ReceiveByteUSART (uint8_t *data);

/**
 * Sets the USART interrupt handler.
 * @param handler The handler function pointer
 */
void SetUSARTInterruptHandler (void (*handler)(uint8_t data));
/**
 * Unsets the USART interrupt handler.
 */
void UnsetUSARTInterruptHandler (void);

#endif
