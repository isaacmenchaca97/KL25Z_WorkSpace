#include <MKL25Z4.H>
#include <string.h>
#include "st7735.h"
#include "fonts.h"
#include "testimg.h"

/*P8_1.c: Send ‘A’ to ‘Z’ via SPI0
* PTD1 pin as SPI SCK
* PTD2 pin as SPI MOSI
* PTD0 pin as SPI SS
*/

void GPIO_init(void);
void UART0_init(void);
void SPI0_init(void);
void delayMs(int n);
void LED_set(int value);
void SPI0_write(unsigned char* data, int size);

int main (void) {
	unsigned char h;
	char c;
	SPI0_init();                 /* enable SPI0 */
	UART0_init();
	GPIO_init();
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_WriteString(0, 0, "Font_7x10, red on black, lorem ipsum dolor sit amet", Font_7x10, ST7735_RED, ST7735_BLACK);
	ST7735_DrawImage(0, 0, ST7735_WIDTH, ST7735_HEIGHT, (uint16_t*)test_img_128x128);
	while (1) {

		while(!(UART0->S1 & 0x20)) {}   /* wait for receive buffer full */
		c = UART0->D; /* read the char received */
		LED_set(c);
	}
 }
  /* initialize UART0 to receive at 9600 Baud */
void UART0_init(void) {
	SIM->SCGC4 |= 0x0400;   /* enable clock for UART0 */
	SIM->SOPT2 |= 0x04000000;    /* use FLL output for UART Baud rate generator*/
	UART0->C2 = 0;          /* turn off UART0 while changing configurations */
	UART0->BDH = 0x00;
	UART0->BDL = 0x89;      /* 9600 Baud */
	UART0->C4 = 0x0F;       /* Over Sampling Ratio 16 */
	UART0->C1 = 0x00;       /* 8-bit data */
	UART0->C2 = 0x04;       /* enable receive */
	SIM->SCGC5 |= 0x0200;   /* enable clock for PORTA */
	PORTA->PCR[1] = 0x0200; /* make PTA1 UART0_Rx pin */
}
  /* initialize all three LEDs on the FRDM board */
void GPIO_init(void){
	SIM->SCGC5 |= 0x400;        /* enable clock to Port B */

	PORTB->PCR[18] = 0x100;     /* make PTB18 pin as GPIO */
	PTB->PDDR |= 0x40000;       /* make PTB18 as output pin */
	PTB->PSOR = 0x40000;        /* turn off red LED */
	PORTB->PCR[8] = 0x100;     /* make PTB8 pin as GPIO CS*/
	PTB->PDDR |= 0x80;       /* make PTB8 as output pin */
	PTB->PSOR = 0x80;        /* turn off pin */
	PORTB->PCR[9] = 0x100;     /* make PTB9 pin as GPIO REST*/
	PTB->PDDR |= 0x100;       /* make PTB9 as output pin */
	PTB->PSOR = 0x100;        /* turn off pin */
	PORTB->PCR[10] = 0x100;     /* make PTB10 pin as GPIO DS*/
	PTB->PDDR |= 0x200;       /* make PTB10 as output pin */
	PTB->PSOR = 0x200;        /* turn off pin */
	PORTB->PCR[19] = 0x100;     /* make PTB19 pin as GPIO */
	PTB->PDDR |= 0x80000;       /* make PTB19 as output pin */
	PTB->PSOR = 0x80000;        /* turn off green LED */
}
  /* initialize SPIO */
void SPI0_init(void) {
	SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
	PORTD->PCR[1] = 0x200;      /* make PTD1 pin as SPI SCK */
	PORTD->PCR[2] = 0x200;      /* make PTD2 pin as SPI MOSI */
	PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
	PTD->PDDR |= 0x01;          /* make PTD0 as output pin for /SS */
	PTD->PSOR = 0x01;           /* make PTD0 idle high */
	SIM->SCGC4 |= 0x400000;     /* enable clock to SPI0 */
	SPI0->C1 = 0x10;            /* disable SPI and make SPI0 master */
	SPI0->BR = 0x60;            /* set Baud rate to 1 MHz */
	SPI0->C1 |= 0x40;           /* Enable SPI module */
}
/* turn on or off the LEDs according to bit 2-0 of the value */
void LED_set(int value){
	if (value != '\n'){
		if (value & 1){   			/* use bit 0 of value to control red LED */
			PTB->PCOR = 0xC0000;    /* turn on red LED */
		}
		else {
			PTB->PSOR = 0xC0000;    /* turn off red LED */
		}
	}
}
/* write a character to SPI0 */
void SPI0_write(unsigned char* data, int size) {
	volatile char dummy;
	for (size_t i = 0; i < size; i++)
	{
		while(!(SPI0->S & 0x20)) { }    /* wait until tx ready */
		SPI0->D = *(data + i);                 /* send register address */
		while(!(SPI0->S & 0x80)) { }    /* wait until tx complete */
		dummy = SPI0->D;                /* clear SPRF */
	}
}