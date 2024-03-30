#ifndef _MYLIBRARY_H_
#define _MYLIBRARY_H_

#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define SCGC5_BASE_ADDR			0x40047000UL
#define SCGC5_PORT_OFFSET		0x1038UL
#define SCGC5_PORT_ENR			(SCGC5_BASE_ADDR + SCGC5_PORT_OFFSET)

#define PORTA_BASE_ADDR			0x40049000UL
#define PORTA_PCR2_OFFSET		0x8UL
#define PORTA_PCR4_OFFSET		0x10UL
#define PORTA_PCR5_OFFSET		0x14UL
#define PORTA_PCR2_ENR			(PORTA_BASE_ADDR + PORTA_PCR2_OFFSET)
#define PORTA_PCR4_ENR			(PORTA_BASE_ADDR + PORTA_PCR4_OFFSET)
#define PORTA_PCR5_ENR			(PORTA_BASE_ADDR + PORTA_PCR5_OFFSET)

#define PORTB_BASE_ADDR			0x4004A000UL
#define PORTB_PCR19_OFFSET		0x4CUL
#define PORTB_PCR19_ENR			(PORTB_BASE_ADDR + PORTB_PCR19_OFFSET)

#define PORTE_BASE_ADDR			0x4004D000UL
#define PORTE_PCR20_OFFSET		0x50UL
#define PORTE_PCR21_OFFSET		0x54UL
#define PORTE_PCR22_OFFSET		0x58UL
#define PORTE_PCR23_OFFSET		0x5CUL
#define PORTE_PCR29_OFFSET		0x74UL
#define PORTE_PCR20_ENR			(PORTE_BASE_ADDR + PORTE_PCR20_OFFSET)
#define PORTE_PCR21_ENR			(PORTE_BASE_ADDR + PORTE_PCR21_OFFSET)
#define PORTE_PCR22_ENR			(PORTE_BASE_ADDR + PORTE_PCR22_OFFSET)
#define PORTE_PCR23_ENR			(PORTE_BASE_ADDR + PORTE_PCR23_OFFSET)
#define PORTE_PCR29_ENR			(PORTE_BASE_ADDR + PORTE_PCR29_OFFSET)

#define PORTD_BASE_ADDR			0x4004C000UL
#define PORTD_PCR0_OFFSET		0x0UL
#define PORTD_PCR1_OFFSET		0x4UL
#define PORTD_PCR2_OFFSET		0x8UL
#define PORTD_PCR3_OFFSET		0xCUL
#define PORTD_PCR4_OFFSET		0x10UL
#define PORTD_PCR5_OFFSET		0x14UL
#define PORTD_PCR6_OFFSET		0x18UL
#define PORTD_PCR7_OFFSET		0x1CUL
#define PORTD_PCR0_ENR			(PORTD_BASE_ADDR + PORTD_PCR0_OFFSET)
#define PORTD_PCR1_ENR			(PORTD_BASE_ADDR + PORTD_PCR1_OFFSET)
#define PORTD_PCR2_ENR			(PORTD_BASE_ADDR + PORTD_PCR2_OFFSET)
#define PORTD_PCR3_ENR			(PORTD_BASE_ADDR + PORTD_PCR3_OFFSET)
#define PORTD_PCR4_ENR			(PORTD_BASE_ADDR + PORTD_PCR4_OFFSET)
#define PORTD_PCR5_ENR			(PORTD_BASE_ADDR + PORTD_PCR5_OFFSET)
#define PORTD_PCR6_ENR			(PORTD_BASE_ADDR + PORTD_PCR6_OFFSET)
#define PORTD_PCR7_ENR			(PORTD_BASE_ADDR + PORTD_PCR7_OFFSET)

#define GPIOA_BASE_ADDR			0x400FF000UL
#define GPIOA_PSOR_OFFSET		0x4UL
#define GPIOA_PSOR_ENR			(GPIOA_BASE_ADDR + GPIOA_PSOR_OFFSET)
#define GPIOA_PCOR_OFFSET		0x8UL
#define GPIOA_PCOR_ENR			(GPIOA_BASE_ADDR + GPIOA_PCOR_OFFSET)
#define GPIOA_PDDR_OFFSET		0x14UL
#define GPIOA_PDDR_ENR			(GPIOA_BASE_ADDR + GPIOA_PDDR_OFFSET)

#define GPIOB_BASE_ADDR			0x400FF040UL
#define GPIOB_PDDR_OFFSET		0x14UL
#define GPIOB_PDDR_ENR			(GPIOB_BASE_ADDR + GPIOB_PDDR_OFFSET)
#define GPIOB_PTOR_OFFSET		0xCUL
#define GPIOB_PTOR_ENR			(GPIOB_BASE_ADDR + GPIOB_PTOR_OFFSET)

#define GPIOE_BASE_ADDR			0x400FF100UL
#define GPIOE_PDDR_OFFSET		0x14UL
#define GPIOE_PDDR_ENR			(GPIOE_BASE_ADDR + GPIOE_PDDR_OFFSET)
#define GPIOE_PDOR_ENR			GPIOE_BASE_ADDR

#define GPIOD_BASE_ADDR			0x400FF0C0UL
#define GPIOD_PDOR_OFFSET		0x0UL
#define GPIOD_PDOR_ENR			(GPIOD_BASE_ADDR + GPIOD_PDOR_OFFSET)
#define GPIOD_PDDR_OFFSET		0x14UL
#define GPIOD_PDDR_ENR			(GPIOD_BASE_ADDR + GPIOD_PDDR_OFFSET)


#define RS 0x04     /* PTA2 mask */
#define RW 0x10     /* PTA4 mask */
#define EN 0x20     /* PTA5 mask */

// configure the GPIOA/D clear, output, set
uint32_t *pGpioaPcorENReg = (uint32_t*)(GPIOA_PCOR_ENR);  // GPIOA_PCOR
uint32_t *pGpioaPsorENReg = (uint32_t*)(GPIOA_PSOR_ENR);  // GPIOA_PSOR
uint32_t *pGpiodPdorENReg = (uint32_t*)(GPIOD_PDOR_ENR);  // GPIOD_PDOR

void delayMs(uint32_t n){
	uint32_t i,j;
	for(i=0 ;i<n ;i++)
		for(j=0 ;j<7000 ;j++);

}
void LCD_command(unsigned char command){
	*pGpioaPcorENReg = RS|RW;		// RS=0, R/W=0
	*pGpioaPsorENReg = EN;			// pulse E
	*pGpiodPdorENReg = command;
	delayMs(0);
	*pGpioaPcorENReg = EN;
	
	if (command < 4)
		delayMs(4);         		// command 1 and 2 needs up to 1.64ms
	else
		delayMs(1);         		// all others 40 us
}
void LCD_data(unsigned char data){
	*pGpioaPsorENReg = RS;			// RS = 1, R/W = 0
	*pGpioaPcorENReg = RW;
	*pGpioaPsorENReg = EN;			// pulse E
	*pGpiodPdorENReg = data;
	delayMs(0);
	*pGpioaPcorENReg = EN;
	delayMs(1);
}
void  LCD_init(void){
	// 1.- configure the SCGC5_PORTD
	uint32_t *pSimScgcdENReg = (uint32_t*)(SCGC5_PORT_ENR);
	*pSimScgcdENReg &= ~(0x1 << 12); 
	*pSimScgcdENReg |= (0x1 << 12); 		// set PORTD

	// 2.- configure the PORTD_PCR
	uint32_t *pPortdPcr0ENReg = (uint32_t*)(PORTD_PCR0_ENR);
	uint32_t *pPortdPcr1ENReg = (uint32_t*)(PORTD_PCR1_ENR);
	uint32_t *pPortdPcr2ENReg = (uint32_t*)(PORTD_PCR2_ENR);
	uint32_t *pPortdPcr3ENReg = (uint32_t*)(PORTD_PCR3_ENR);
	uint32_t *pPortdPcr4ENReg = (uint32_t*)(PORTD_PCR4_ENR);
	uint32_t *pPortdPcr5ENReg = (uint32_t*)(PORTD_PCR5_ENR);
	uint32_t *pPortdPcr6ENReg = (uint32_t*)(PORTD_PCR6_ENR);
	uint32_t *pPortdPcr7ENReg = (uint32_t*)(PORTD_PCR7_ENR);
	*pPortdPcr0ENReg &= ~(0x7 << 8);
	*pPortdPcr1ENReg &= ~(0x7 << 8);
	*pPortdPcr2ENReg &= ~(0x7 << 8);
	*pPortdPcr3ENReg &= ~(0x7 << 8);
	*pPortdPcr4ENReg &= ~(0x7 << 8);
	*pPortdPcr5ENReg &= ~(0x7 << 8);
	*pPortdPcr6ENReg &= ~(0x7 << 8);
	*pPortdPcr7ENReg &= ~(0x7 << 8);
	*pPortdPcr0ENReg |= (0x1 << 8); 		// alternative 1 (GPIO)
	*pPortdPcr1ENReg |= (0x1 << 8);
	*pPortdPcr2ENReg |= (0x1 << 8);
	*pPortdPcr3ENReg |= (0x1 << 8);
	*pPortdPcr4ENReg |= (0x1 << 8);
	*pPortdPcr5ENReg |= (0x1 << 8);
	*pPortdPcr6ENReg |= (0x1 << 8);
	*pPortdPcr7ENReg |= (0x1 << 8);

	// 3.- configure the GPIOD_PDDR_ENR
	uint32_t *pGpiodPddrENReg = (uint32_t*)(GPIOD_PDDR_ENR);
	*pGpiodPddrENReg |= (0xFF << 0); 		// make PTD7-0 as output pins (1111 1111)

	// 4.- configure the SCGC5_PORTA
	uint32_t *pSimScgcaENReg = (uint32_t*)(SCGC5_PORT_ENR);
	*pSimScgcaENReg &= ~(0x1 << 9); 		// clear bit 9 PORTA
	*pSimScgcaENReg |= (0x1 << 9);	

	// 5.- configure PORTA_PCR
	uint32_t *pPortaPcr2ENReg = (uint32_t*)(PORTA_PCR2_ENR);
	uint32_t *pPortaPcr4ENReg = (uint32_t*)(PORTA_PCR4_ENR);
	uint32_t *pPortaPcr5ENReg = (uint32_t*)(PORTA_PCR5_ENR);
	*pPortaPcr2ENReg &= ~(0x7 << 8); 		// clear mux PCR[]
	*pPortaPcr4ENReg &= ~(0x7 << 8);
	*pPortaPcr5ENReg &= ~(0x7 << 8);
	*pPortaPcr2ENReg |= (0x1 << 8); 		// alternative 1 (GPIO)
	*pPortaPcr4ENReg |= (0x1 << 8);
	*pPortaPcr5ENReg |= (0x1 << 8);

	// 6.- configure GPIOA_PDDR_ENR
	uint32_t *pGpioaPddrENReg = (uint32_t*)(GPIOA_PDDR_ENR);
	*pGpioaPddrENReg |= (0x34 << 0); 		// make PORTA 5, 4, 2 as output pins (0011 0100)

	*pGpioaPcorENReg = RS|RW;		// RS=0, R/W=0
	*pGpioaPcorENReg = EN;			// pulse E

	delayMs(30);   							// initialization sequence
	LCD_command(0x38);
	delayMs(10);
	LCD_command(0x38);
	delayMs(10);
	LCD_command(0x38);
	delayMs(1);
	LCD_command(0x0F);						// turn on display, cursor blinking
	delayMs(1);
	LCD_command(0x01);						// clear screen, move cursor to home
	delayMs(1);

	// LCD_command(0x30);
	// LCD_command(0x38);						// set 8-bit data, 2-lin, 5x7 font
	// LCD_command(0x06);						// move cursor right
}

void ledToggle(void){
	// 1.- configure the SCGC5_PORTB
	uint32_t *pSimScgcbENReg = (uint32_t*)(SCGC5_PORT_ENR);
	*pSimScgcbENReg &= ~(1 << 10); // clear bit 10 PORTB
	*pSimScgcbENReg |= (1 << 10);

	// 2.- configure the PORTB_PCR19_ENR
	uint32_t *pPortbPcr19ENReg = (uint32_t*)(PORTB_PCR19_ENR);
	*pPortbPcr19ENReg &= ~(0x7 << 8); // clear mux PCR[19]
	*pPortbPcr19ENReg |= (0x1 << 8); // alternative 1 (GPIO)

	// 3.- configure the GPIOB_PDDR_ENR
	uint32_t *pGpioBPddrENReg = (uint32_t*)(GPIOB_PDDR_ENR);
	*pGpioBPddrENReg |= (0x1 << 19); // set as output

	// 4.- configure GPIOB_PTOR_ENR
	uint32_t *pGpioBPtor = (uint32_t*)(GPIOB_PTOR_ENR);

	while (1)
	{
		*pGpioBPtor |= (0x1 << 19);
		delayMs(100);
	}
}
int sumaRecursiva(int n) {
    if (n == 0) {
        return 0;
    } else {
        return n + sumaRecursiva(n-1);
    }
}
void counterLed(void){
	// 1.- configure the SCGC5_PORTE
	uint32_t *pSimScgceENReg = (uint32_t*)(SCGC5_PORT_ENR);
	*pSimScgceENReg &= ~(1 << 13); // clear bit 13 PORTE
	*pSimScgceENReg |= (1 << 13);

	// 2.- configure the PORTE_PCR
	uint32_t *pPortePcr20ENReg = (uint32_t*)(PORTE_PCR20_ENR);
	uint32_t *pPortePcr21ENReg = (uint32_t*)(PORTE_PCR21_ENR);
	uint32_t *pPortePcr22ENReg = (uint32_t*)(PORTE_PCR22_ENR);
	uint32_t *pPortePcr23ENReg = (uint32_t*)(PORTE_PCR23_ENR);
	uint32_t *pPortePcr29ENReg = (uint32_t*)(PORTE_PCR29_ENR);
	*pPortePcr20ENReg &= ~(0x7 << 8); // clear mux PCR[20]
	*pPortePcr21ENReg &= ~(0x7 << 8); // clear mux PCR[21]
	*pPortePcr22ENReg &= ~(0x7 << 8); // clear mux PCR[22]
	*pPortePcr23ENReg &= ~(0x7 << 8); // clear mux PCR[23]
	*pPortePcr29ENReg &= ~(0x7 << 8); // clear mux PCR[29]
	*pPortePcr20ENReg |= (0x1 << 8); // alternative 1 (GPIO)
	*pPortePcr21ENReg |= (0x1 << 8); // alternative 1 (GPIO)
	*pPortePcr22ENReg |= (0x1 << 8); // alternative 1 (GPIO)
	*pPortePcr23ENReg |= (0x1 << 8); // alternative 1 (GPIO)
	*pPortePcr29ENReg |= (0x1 << 8); // alternative 1 (GPIO)

	// 3.- configure the GPIOE_PDDR_ENR

}

#endif  /* _MYLIBRARY_H_ */