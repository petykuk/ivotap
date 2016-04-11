#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "head.h"

#define FOSC 1000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void portinit()
{
DDRB=0x00;
DDRC=0xff;
DDRD=0xff;
}


void usartinit(unsigned int ubrr)
{
	PRR=(0<<PRUSART0); //usart clock enable(power management)
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void usartransmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
data=0xf0;
/* Put data into buffer, sends the data */
UDR0 = data;
}

