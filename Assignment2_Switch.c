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
int upflag;
int downflag;
int counts = 0;
int Num[4] = {0xC0, 0xF9, 0xA4, 0xB0}; // 순서대로 0, 1, 2, 3 에 해당하는 desplay

ISR(INT0_vect)
{upflag = 1;}

ISR(INT1_vect)
{downflag = 1;}
		
int main(void)
{
	init_devices();
	
	while (1) 
    {
		if(upflag==1){
			if(counts<3)
				counts++;
			upflag=0;
		}
		
		if(downflag==1){
			if(counts>0)
				counts--;
			downflag=0;
		}
		
		PORTE = Num[counts];
		delay(20);
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
	EICRA = 0x0F; // extended ext ints
	//EICRB = 0x00; // extended ext ints
	EIMSK = (1<<INT0)|(1<<INT1); // EINTO, 1 enabled 
	// the above is same with EIMSK = 0x03
	TIMSK = 0x00; // timer interrupt sources
//	ETIMSK = 0x00; // extended timer interrupt sources
	sei(); // re-enable interrupt
	//all peripherals are now initialized
}

void port_init(void)
{
	PORTA = 0x00; DDRA = 0xFF;
	PORTB = 0x00; DDRB = 0xFF;
	PORTC = 0x00; DDRC = 0xFF;
	PORTD = 0x00; DDRD = 0xFF & ~((1<<PIND0)|(1<<PIND1));
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
