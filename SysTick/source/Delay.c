#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define LEDRGB_GREEN     0x80000
#define RELOAD_VALUE     0xA3D3

void LED_init(void);
void DelayMs(uint64_t);

int main(void){
    
    LED_init();

    while (1)
    {
        GPIOB->PTOR = LEDRGB_GREEN;
        DelayMs(1000);
    }
    
    return 0;
}
void LED_init(void){
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;     //eneable clock of portB
    PORTB->PCR[19] |= PORT_PCR_MUX(1);      //mus gpio led green
    GPIOB->PDDR |= LEDRGB_GREEN;            //PIN 19 as outputs
}
void DelayMs(uint64_t count){
    SysTick->LOAD = RELOAD_VALUE;           //reload with number of clocks per 1 ms solo si el clock es de 41.94MH
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;      //enable it, no interrupt, use system clock

    for (size_t i = 0; i < count; i++)
    {
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    }
    SysTick->CTRL = 0;      //Stop the timer (Enable = 0)   
    
}