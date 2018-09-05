
#ifndef USARTMANAGER_H
#define USARTMANAGER_H

#define USART_DEFAULT_BAUD 9600

void InitializeUSART (void);
void InitializeUSARTWithBAUD (unsigned int ubbr);

void TransmitUSART (uint8_t *data, int length);
void TransmitByteUSART (uint8_t data);
void ReceiveUSART (uint8_t *data, int length);
void ReceiveByteUSART (uint8_t *data);

void SetUSARTInterruptHandler (void (*handler)(uint8_t data));
void UnsetUSARTInterruptHandler (void);

#endif
