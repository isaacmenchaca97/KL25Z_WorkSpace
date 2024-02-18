#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

#define LEDRGB_BLUE   0x2

void TPMO_init(void);
void LEDRGB_init(void);

int main(){

  TPMO_init();
  LEDRGB_init();

  while (1){
    while (!(TPM0->SC & TPM_SC_TOF_MASK)){}    //wait until the TOF is set
    TPM0->SC |= TPM_SC_TOF_MASK;               //clear TOF
    GPIOD->PTOR = LEDRGB_BLUE;                  //toggle blue LED
  }
  return 0;
}
void TPMO_init(void){
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;      //TPM0 Clock Gate Control
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);      //UART0 clock source select, MCGFLLCLK clock or MCGPLLCLK/2 clock
  TPM0->SC = 0;                           //disable timer while the configuration is being modified
  TPM0->MOD |= TPM_MOD_MOD_MASK;          //max modulo value
  TPM0->SC |= TPM_SC_PS(7);					      /*	prescalador Divide by 128	*/
  TPM0->SC |= TPM_SC_TOF_MASK;            //clear TOF
  TPM0->SC |= TPM_SC_CMOD(1);             //enable timer free-running mode
}
void LEDRGB_init(void){
   SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
   PORTD->PCR[1] |= PORT_PCR_MUX(1);
   GPIOD->PDDR = LEDRGB_BLUE;
}

