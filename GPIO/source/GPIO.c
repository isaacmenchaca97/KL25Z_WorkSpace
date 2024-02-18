#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define SCGC5_BASE_ADDR			0x40047000UL
#define SCGC5_PORTB_OFFSET		0x1038UL
#define SCGC5_PORTB_ENR			(SCGC5_BASE_ADDR + SCGC5_PORTB_OFFSET)

#define PORTB_BASE_ADDR			0x4004A000UL
#define PORTB_PCR19_OFFSET		0x4CUL
#define PORTB_PCR19_ENR			(PORTB_BASE_ADDR + PORTB_PCR19_OFFSET)

#define GPIOB_BASE_ADDR			0x400FF040UL
#define GPIOB_PDDR_OFFSET		0x14UL
#define GPIOB_PDDR_ENR			(GPIOB_BASE_ADDR + GPIOB_PDDR_OFFSET)

#define GPIOB_PTOR_OFFSET		0xCUL
#define GPIOB_PTOR_ENR			(GPIOB_BASE_ADDR + GPIOB_PTOR_OFFSET)

// #define GREEN_LED			0x80000
// #define BOTTON				0x100
// #define PULL_UP_BOTTON		0x103

void delayMs(uint32_t n);

int main(){

	// 1.- configure the SCGC5_PORTB
	uint32_t *pSimScgcENReg = (uint32_t*)(SCGC5_PORTB_ENR);
	*pSimScgcENReg &= ~(1 << 10); //clear bit 10
	*pSimScgcENReg |= (1 << 10);

	// 2.- configure the PORTB_PCR19_ENR
	 uint32_t *pPortbPcr19ENReg = (uint32_t*)(PORTB_PCR19_ENR);
	 *pPortbPcr19ENReg &= ~(0x7 << 8); //mux PCR[19]
	 *pPortbPcr19ENReg |= (0x1 << 8); //Alternative 1 (GPIO)

	// 3.- configure the GPIOB_PDDR_ENR
	uint32_t *pGpioBPddrENReg = (uint32_t)(GPIOB_PDDR_ENR);
	*pGpioBPddrENReg |= (0x1 << 19); //set as output

	uint32_t *pGpioBPtor = (uint32_t)(GPIOB_PTOR_ENR);

	while (1)
	{
		*pGpioBPtor |= (0x1 << 19);
		delayMs(50);
	}
	

	// SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	// PORTB->PCR[19] |= PORT_PCR_MUX(1);
	// PORTB->PCR[8] |= PULL_UP_BOTTON;

	// GPIOB->PDDR |= GREEN_LED;
	// GPIOB->PDDR &= ~BOTTON;

	// while(1){
	// 	if(GPIOB->PDIR & BOTTON){
	// 		GPIOB->PDOR &= ~GREEN_LED;
	// 		delayMs(50);
	// 		GPIOB->PDOR |= GREEN_LED;
	// 		delayMs(50);
	// 		GPIOB->PTOR = GREEN_LED;
	// 		delayMs(50);
	// 		GPIOB->PTOR = GREEN_LED;
	// 		delayMs(50);
	// 	}
	// 	else{
	// 		GPIOB->PSOR = GREEN_LED;
	// 	}


	// }


	return 0;
}
void delayMs(uint32_t n){
	uint32_t i,j;
	for(i=0 ;i<n ;i++)
		for(j=0 ;j<7000 ;j++);

}
