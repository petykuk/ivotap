#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int i;
int b;
//---------------------------------------------------------------------------------------------------------
void timer0init() //for timeing.
{
 PRR=(0<<PRTIM0); // enableing timer0 in power management
  TCCR0A = (0<<WGM00) 
		| (0<<WGM01) 
		| (0<<COM0A0) 
		| (0<<COM0A1);
  TCCR0B = (0<<WGM02)
		| (1<<CS00) 
		| (0<<CS01) 
		| (0<<CS02); //same if i set it up with 0b110101.....
 	TIMSK0 = (1<<TOIE0); //timer mask, enables interrupt.
	sei(); //global interrupt set
}

ISR(TIMER0_OVF_vect)//timer0 overlfow vector. It saves initial state, does the inside of this function, and then goes back where it stopped the program
{
i++;
if(i==1980)
	{
	//PORTC=PORTC^1;
	i=0;
	}	
}
//----------------------------------------------------------------------------------------------------------------
void timer1() //conting button input
{
PRR=(0<<PRTIM1); // enableing timer1 in power management
  TCCR1A = (0<<WGM11) //mode of operation
		| (0<<WGM10)  //mode of operation
		| (0<<COM1A0) 
		| (0<<COM1A1);
  TCCR1B = (0<<WGM13) //mode of operation
  		|  (0<<WGM12) //mode of operation
		| (0<<CS12) 
		| (0<<CS11) 
		| (1<<CS10); //same if i set it up with 0b110101.....
 	TIMSK1 = (1<<TOIE1); //timer mask, enables interrupt.
	sei(); //global interrupt set
	TCNT1H=0xef;
	TCNT1L=0xff;
}

ISR(TIMER1_OVF_vect)//timer1 overlfow vector. It saves initial state, does the inside of this function, and then goes back where it stopped the program
{
	PORTD=PORTD^1;	
}
//-----------------------------------------------------------------------------------------------------------	
int main()
{
portinit();
timer0init();
usartinit();
//timer1();
	while(1)
		{
		 	while(PINB & (1<<PB0)==1)
			{
				PORTC=PORTC^1;
				b++;
					PORTC=b;
					_delay_ms(3);
				usartransmit();
			}
		}
}
