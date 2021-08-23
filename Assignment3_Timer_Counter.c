/*
 * AM128Hello.c
 *
 * Created: 2021-07-13 오후 5:17:46
 * Author : kjw03
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

void port_case(void);
void port_init(void);
void init_devices(void);
void delay(int cnt);
int countflag;
int counts = 0;
int Num[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

ISR(TIMER0_OVF_vect)
{TCNT0=-125; countflag++;}

int main(void)
{
	init_devices();
	
	while (1) 
    {	
		if(countflag==125){
			if(counts<9)
				counts++;
			else
				counts=0;
			countflag=0;
		}
		PORTE = Num[counts];
    }
	
	return 0;
}

void init_devices(void)
{
	// stop errant interrupts until set up
	cli();
	XMCRA = 0x00; // external memory
	XMCRB = 0x00; // external memory
	port_init();
	
	MCUCR = 0x00;
	//External Interrupt
	EICRA = 0x00; // extended ext ints
	EICRB = 0x00; // extended ext ints
	EIMSK = 0x00; // 
	
	//Timer
	TCCR0 = (1<<CS02)|(1<<CS01)|(1<<CS00); // 1/(16M/1024)
	TIMSK = (1<<TOIE0); // timer interrupt sources
	ETIMSK = 0x00; // extended timer interrupt sources
	
	sei(); // re-enable interrupt
	//all peripherals are now initialized
}

void port_init(void)
{
	PORTA = 0x00; DDRA = 0xFF;
	PORTB = 0x00; DDRB = 0xFF;
	PORTC = 0x00; DDRC = 0xFF;
	PORTD = 0x00; DDRD = 0xFF;
	PORTE = 0x00; DDRE = 0xFF;
	PORTF = 0x00; DDRF = 0xFF;
	PORTG = 0x00; DDRG = 0xFF;
}
