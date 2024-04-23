#include <MKL25Z4.H>
void UART2_init(void);
void delayMs(int n);

int main (void) {
	char message[] = "Hello\n";
	char c;
	int i;
	UART2_init();
	while (1) {
		for (i = 0; i < 6; i++) {
			while(!(UART2->S1 & 0x80)) {}   /* wait for transmit buffer empty */
			UART2->D = message[i]; /* send a char */
		}
		while(!(UART2->S1 & 0x20)) {}   /* wait for receive buffer full */
		c = UART2->D ; /* read the char received */
		
		delayMs(10); /* leave a gap between messages */
	}
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