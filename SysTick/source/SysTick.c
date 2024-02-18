#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define LEDRGB_GREEN     0x80000
#define LEDRGB_RED       0x40000

void LED_init(void);
void SysTick_init(void);

int main(){

    uint32_t c;

    LED_init();
    SysTick_init();

    while (1)
    {
        c = SysTick->VAL;       //read current value of down counter
        GPIOB->PDOR = c >> 4;   //line up counter MSB with LED
    }
    

    return 0;
}
void LED_init(void){
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;     //eneable clock of portB
    PORTB->PCR[18] |= PORT_PCR_MUX(1);      //mux gpio led red
    PORTB->PCR[19] |= PORT_PCR_MUX(1);      //mus gpio led green
    GPIOB->PDDR |= LEDRGB_GREEN | LEDRGB_RED;    //PIN 18 & 19 as outputs
}
void SysTick_init(void){
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;   //max value of count 16,777,216
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;  //enable it, no interrupt, use system clock

}
