#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>

void TPMO_init(void);
void LEDRGB_init(void);

int main(){
  unsigned short then = 0;
  unsigned short now = 0;
  unsigned short diff;

  TPMO_init();
  LEDRGB_init();

  while (1) {

    while(!(TPM2->CONTROLS[0].CnSC & 0x80)) { } /* wait until the CHF is set */

      TPM2->CONTROLS[0].CnSC |= 0x80; /* clear CHF */
      now = TPM2->CONTROLS[0].CnV;
      diff = now - then; /* you may put a breakpoint here and examine the values */
      then = now; /* save the current counter value for next calculation */
      
      /* change LEDs according to bit 11-9 of the value of diff */
      diff = diff >> 9;
      if(diff&1) /*usebit0ofdifftocontrolredLED*/
      PTB->PCOR = 0x40000; /* turn on red LED */
      else
      PTB->PSOR = 0x40000; /* turn off red LED */
      if (diff & 2)    /* use bit 1 of diff to control green LED */
      PTB->PCOR = 0x80000; /* turn on green LED */
      else
      PTB->PSOR = 0x80000; /* turn off green LED */
      if (diff & 4)    /* use bit 2 of diff to control blue LED */
      PTD->PCOR = 0x02; /* turn on blue LED */
      else
      PTD->PSOR = 0x02; /* turn off blue LED */
      /* end of LED code */
  }

  return 0;
}
void TPMO_init(void){
  SIM->SCGC5 |= 0x0200; /* enable clock to Port A */
  PORTA->PCR[1] = 0x0300; /* set PTA1 pin for TPM2CH0 */
  SIM->SCGC6 |= 0x04000000; /* enable clock to TPM2 */
  SIM->SOPT2 |= 0x01000000; /* use MCGFLLCLK as timer counter clock */
  TPM2->SC = 0; /* disable timer while configuring */
  TPM2->SC = 0x07; /* prescaler /128 */
  TPM2->MOD = 0xFFFF; /* max modulo value */
  TPM2->CONTROLS[0].CnSC = 0x04; /* IC rising edge */
  TPM2->SC |= 0x08; /* enable timer */
}
void LEDRGB_init(void){
  SIM->SCGC5 |= 0x400; /* enable clock to Port B */
  SIM->SCGC5 |= 0x1000; /* enable clock to Port D */
  PORTB->PCR[18] = 0x100; /* make PTB18 pin as GPIO */
  PTB->PDDR |= 0x40000; /* make PTB18 as output pin */
  PORTB->PCR[19] = 0x100; /* make PTB19 pin as GPIO */
  PTB->PDDR |= 0x80000; /* make PTB19 as output pin */
  PORTD->PCR[1] = 0x100; /* make PTD1 pin as GPIO */
  PTD->PDDR |= 0x02; /* make PTD1 as output pin */
}
