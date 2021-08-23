/*
 * AM128Hello.c
 *
 * Created: 2021-07-13 오후 5:17:46
 * Author : kjw03
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void port_init(void);
void init_devices(void);
void delay(int cnt);

int main(void)
{
	//int i;
	int time_interval = 300;
	init_devices();
	
    /* Replace with your application code */
    while (1) 
    {
		//for(i=0; i<8; i++)
		//{
			// 7-segment test
			//PORTE=~(1<<i);
			
			//delay(150);
		//}
		PORTE=0xC0; // 0
		delay(time_interval);
		PORTE=0x79; // 1.
		delay(time_interval);
		PORTE=0xA4; // 2
		delay(time_interval);
		PORTE=0x30; // 3.
		delay(time_interval);
		PORTE=0x99; // 4
		delay(time_interval);
		PORTE=0x12; // 5.
		delay(time_interval);
		PORTE=0x82; // 6
		delay(time_interval);
		PORTE=0x78; // 7.
		delay(time_interval);
		PORTE=0x80; // 8
		delay(time_interval);
		PORTE=0x10; // 9.
		delay(time_interval);
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
	EICRA = 0x00; // external ext ints
	EICRB = 0x00; // external ext ints
	EIMSK = 0x00;
	TIMSK = 0x00; // timer interrupt sources
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

void delay(int cnt)
{
	int i, j;
	for(i=0;i<=700;i++){
		for(j=0;j<=cnt;j++){
			
		}
	}
}
