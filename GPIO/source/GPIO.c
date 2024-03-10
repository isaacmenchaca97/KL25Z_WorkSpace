#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define SCGC5_BASE_ADDR			0x40047000UL
#define SCGC5_PORT_OFFSET		0x1038UL
#define SCGC5_PORT_ENR			(SCGC5_BASE_ADDR + SCGC5_PORT_OFFSET)

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

#define GPIOB_BASE_ADDR			0x400FF040UL
#define GPIOB_PDDR_OFFSET		0x14UL
#define GPIOB_PDDR_ENR			(GPIOB_BASE_ADDR + GPIOB_PDDR_OFFSET)
#define GPIOB_PTOR_OFFSET		0xCUL
#define GPIOB_PTOR_ENR			(GPIOB_BASE_ADDR + GPIOB_PTOR_OFFSET)

#define GPIOE_BASE_ADDR			0x400FF100UL
#define GPIOE_PDDR_OFFSET		0x14UL
#define GPIOE_PDDR_ENR			(GPIOE_BASE_ADDR + GPIOE_PDDR_OFFSET)
#define GPIOE_PDOR_ENR			GPIOE_BASE_ADDR


void delayMs(uint32_t n);
void ledToggle(void);
int sumaRecursiva(int n);
void counterLed(void);

int main(){
	

	return 0;
}
void delayMs(uint32_t n){
	uint32_t i,j;
	for(i=0 ;i<n ;i++)
		for(j=0 ;j<7000 ;j++);

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
