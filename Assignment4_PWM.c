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
int Flag = 0;
int counts = 0;

ISR(TIMER1_OVF_vect)
{Flag=1;}
ISR(TIMER1_COMPC_vect)
{}

int main(void)
{
	init_devices();
	
	while (1) 
    {
		if(Flag){
			counts++;
			Flag = 0;
		}
		if(counts == 100){
			if(OCR1CL==0xFF){
				OCR1CL = 0x00;
				counts = 0;
			}
			else{
				OCR1CL = OCR1CL+0x01;
				counts = 0;
			}
		}
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
	
	TCNT1L = 0x00;
	OCR1CL = 0x00;
	
	//Timer
	TCCR1A = (1<<COM1C1)|(1<<WGM10);
	TCCR1B = (0<<CS10)|(1<<CS11)|(0<<CS12)|(1<<WGM12);
	TIMSK = (1<<TOIE1)|(1<<OCIE1C); // timer interrupt sources
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
	PORTE = 0xFF; DDRE = 0xFF;
	PORTF = 0x00; DDRF = 0xFF;
	PORTG = 0x00; DDRG = 0xFF;
}
