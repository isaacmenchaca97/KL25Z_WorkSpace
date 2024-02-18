#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define LEDRGB_RED		0x40000
#define LEDRGB_GREEN	0x80000
#define LEDRGB_BLUE		0x2


void UART0_init(void);
void LED_init(void);
void LED_Set(uint8_t);

int main(){

	uint8_t c;

	UART0_init();
	LED_init();

	while(1){
		/*while(!(UART0->S1 & UART0_S1_TDRE_MASK));	//wait for transmit buffer empty
		UART0->D = 'Y';
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));	//wait for transmit buffer empty
		UART0->D = 'e';
		while(!(UART0->S1 & UART0_S1_TDRE_MASK));	//wait for transmit buffer empty
		UART0->D = 's';
		delayMs(50);*/

		while(!(UART0->S1 & UART0_S1_RDRF_MASK));	//wait for receive buffer full
		c = UART0->D;
		LED_Set(c);	


	}

	return 0;
}
void UART0_init(void){
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;		//Clock to port UART0
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);	//UART0 clock source select. PLL/FLL clock select
	UART0->C2 = 0;							//Turn off the UART0 before changing configurations by clearing UART0_C2 register.
	UART0->BDH = 0;
	UART0->BDL = UART0_BDL_SBR(23);			//Baud Rate Modulo Divisor 115,200 "con estos valores funcionó como 57600"
	UART0->C4 = UART0_C4_OSR(15);			//Over Sampling Ratio 16
	UART0->C1 = 0;							//8-Bit Mode Select
	UART0->C2 |= UART0_C2_RE_MASK;			//Receiver Enable
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;		//Port A Clock Gate Control
	PORTA->PCR[1] |= PORT_PCR_MUX(2);		//UART0_Rx
}
void LED_init(void){
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;		//PORTB clock gate control
	PORTB->PCR[18] |= PORT_PCR_MUX(1);		//Pin MUX control
	GPIOB->PDDR |= LEDRGB_RED;				//Port Data Direction
	GPIOB->PTOR = LEDRGB_RED;
	PORTB->PCR[19] |= PORT_PCR_MUX(1);
	GPIOB->PDDR |= LEDRGB_GREEN;
	GPIOB->PTOR = LEDRGB_GREEN;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;		//PORTD clock gate control
	PORTD->PCR[1] |= PORT_PCR_MUX(1);		//Pin MUX control
	GPIOD->PDDR |= LEDRGB_BLUE;
	GPIOD->PTOR = LEDRGB_BLUE;

}
void LED_Set(uint8_t led){
	
	switch (led)
	{
	case 'R':
		GPIOB->PTOR = LEDRGB_RED;
		break;
	case 'G':
		GPIOB->PTOR = LEDRGB_GREEN;
		break;
	case 'B':
		GPIOD->PTOR = LEDRGB_BLUE;
	
	default:
		//NOTHING TO DO
		break;
	}
}

