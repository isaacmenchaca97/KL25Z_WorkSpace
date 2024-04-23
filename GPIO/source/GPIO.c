#include <MKL25Z4.H>
void UART2_init(void);
void delayMs(int n);
void LED_init(void);
void LED_set(char value);

int main (void) {
	char message[] = "AT+START";
	// char c;
	int i;

	LED_init();
	UART2_init();

	while (1) {
		for (i = 0; i < 8; i++) {
			while(!(UART2->S1 & 0x80)) {}   /* wait for transmit buffer empty */
			UART2->D = message[i]; /* send a char */
		}
		while(!(UART2->S1 & 0x20)) {}   /* wait for receive buffer full */
		//c = UART2->D ; /* read the char received */
		printf("%s\n", UART2->D);
		
		//LED_set(c);
	}
}
/* initialize all three LEDs on the FRDM board */
void LED_init(void)
{
	SIM->SCGC5 |= 0x400;        /* enable clock to Port B */
	PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
	PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
	PTB->PSOR = 0x40000;        /* turn off red LED */
}
/* turn on or off the LEDs according to bit 2-0 of the value */
void LED_set(char value)
{
	if (value == "1")    			/* use bit 0 of value to control red LED */
		PTB->PCOR = 0x40000;    /* turn on red LED */
	else
		PTB->PSOR = 0x40000;    /* turn off red LED */
}
/* initialize UART2 to transmit and receive at 9600 Baud */
void UART2_init(void) {
	SIM->SCGC4 |= 0x1000;   /* enable clock to UART2 */
	UART2->C2 = 0;          /* disable UART during configuration */
	UART2->BDH = 0x00;
	UART2->BDL = 0x5B;      /* 9600 Baud */
	UART2->C1 = 0x00;       /* normal 8-bit, no parity */
	UART2->C3 = 0x00;       /* no fault interrupt */
	UART2->C2 = 0x0C;       /* enable transmit and receive */
	SIM->SCGC5 |= 0x1000;   /* enable clock to PORTD */
	PORTD->PCR[5] = 0x300;  /* PTD5 for UART2 transmit */
	PORTD->PCR[4] = 0x300;  /* PTD5 for UART2 receive */
}

/* Delay n milliseconds */
/* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit(). */
void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for (j = 0; j < 7000; j++) {}
}