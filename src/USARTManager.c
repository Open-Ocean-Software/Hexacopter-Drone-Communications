
#include "USARTManager.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void (*intHandler)(uint8_t data) = 0;

void InitializeUSART (void)
{
    InitializeUSARTWithBAUD(USART_DEFAULT_BAUD);
}

void InitializeUSARTWithBAUD (unsigned int ubrr)
{
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)(ubrr);
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8 data bits, 2 stop bits
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void TransmitUSART (uint8_t *data, int length)
{
    for (int i = 0; i < length; i++) {
        TransmitByteUSART(data[i]);
    }
}
void TransmitByteUSART (uint8_t data)
{
    transmitByte(data);
}

void ReceiveUSART (uint8_t *data, int length)
{
    data = malloc(sizeof(uint8_t) * length);
    for (int i = 0; i < length; i++) {
        ReceiveByteUSART(&(data[i]));
    }
}
void ReceiveByteUSART (uint8_t *data)
{
    ReceiveByteUSART(data);
}

void SetUSARTInterruptHandler (void (*handler)(uint8_t data))
{
    intHandler = handler;
}
void UnsetUSARTInterruptHandler (void)
{
    intHandler = 0;
}

void transmitByte (unsigned char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE))) ;
    // Inject data into buffer, sends data
    UDR0 = data;
}

void receiveByte (unsigned char *data)
{
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC))) ;
    // Extract data from buffer
    *data = UDR0;
}

ISR(USART_RX_vect)
{
    if (intHandler != 0) {
        uint8_t buffer;
        receiveByte(&buffer);
        intHandler(data);
    }
}
