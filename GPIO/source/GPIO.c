/* p3_1.c: Initialize and display “Hello” on the LCD using 8-bit data mode.
* Data pins use Port D, control pins use Port A.
* This program does not poll the status of the LCD.
* It uses delay to wait out the time LCD controller is busy.
* Timing is more relax than the HD44780 datasheet to accommodate the
* variations among the LCD modules.
* You may want to adjust the amount of delay for your LCD controller.
*/
#include <MKL25Z4.H>
#define RS 0x04     /* PTA2 mask */
#define RW 0x10     /* PTA4 mask */
#define EN 0x20     /* PTA5 mask */
void delayMs(int n);
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init(void);

int main(void)
{
	LCD_init();
	for(;;)
	{
		LCD_command(1);         /* clear display */
		delayMs(500);
		LCD_command(0x2);      /* set cursor at first line */
		LCD_data('h');          /* write the word */
		LCD_data('o');
		LCD_data('l');
		LCD_data('l');
		LCD_data('o');
		delayMs(500);
 	}
 }
void LCD_init(void)
{
	SIM->SCGC5 |= 0x1000;       /* enable clock to Port D */
	PORTD->PCR[0] = 0x100;      /* make PTD0 pin as GPIO */
	PORTD->PCR[1] = 0x100;      /* make PTD1 pin as GPIO */
	PORTD->PCR[2] = 0x100;      /* make PTD2 pin as GPIO */
	PORTD->PCR[3] = 0x100;      /* make PTD3 pin as GPIO */
	PORTD->PCR[4] = 0x100;      /* make PTD4 pin as GPIO */
	PORTD->PCR[5] = 0x100;      /* make PTD5 pin as GPIO */
	PORTD->PCR[6] = 0x100;      /* make PTD6 pin as GPIO */
	PORTD->PCR[7] = 0x100;      /* make PTD7 pin as GPIO */
	PTD->PDDR = 0xFF;           /* make PTD7-0 as output pins */

	SIM->SCGC5 |= 0x0200;       /* enable clock to Port A */
	PORTA->PCR[2] = 0x100;      /* make PTA2 pin as GPIO */
	PORTA->PCR[4] = 0x100;      /* make PTA4 pin as GPIO */
	PORTA->PCR[5] = 0x100;      /* make PTA5 pin as GPIO */
	PTA->PDDR |= 0x34;          /* make PTA5, 4, 2 as output pins */

	delayMs(30);                /* initialization sequence */
	LCD_command(0x30);
	delayMs(10);
	LCD_command(0x30);
	delayMs(1);
	LCD_command(0x30);
	LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
	LCD_command(0x06);      /* move cursor right */
	LCD_command(0x01);      /* clear screen, move cursor to home */
	LCD_command(0x0F);      /* turn on display, cursor blinking */
}
void LCD_command(unsigned char command)
{
	PTA->PCOR = RS|RW; /*RS=0,R/W=0*/
	PTD->PDOR = command;
	PTA->PSOR = EN;         /* pulse E */
	delayMs(0);
	PTA->PCOR = EN;
	if (command < 4)
		delayMs(4);         /* command 1 and 2 needs up to 1.64ms */
	else
		delayMs(1);         /* all others 40 us */
}
void LCD_data(unsigned char data)
{
	PTA->PSOR = RS;         /* RS = 1, R/W = 0 */
	PTA->PCOR = RW;
	PTD->PDOR = data;
	PTA->PSOR = EN;         /* pulse E */
	delayMs(0);
	PTA->PCOR = EN;
	delayMs(1);
}
 
/* Delay n milliseconds
* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
*/
void delayMs(int n) 
{
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++) { }
}