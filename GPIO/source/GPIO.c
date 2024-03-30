#include <stdio.h>
#include <stdint.h>
#include <MKL25Z4.h>
#include "mylibrary.h"


int main(){
	LCD_init();
	while (1)
	{
		LCD_command(1);			// clear display
		delayMs(500);
		LCD_command(0x800);		// set cursor at first line
		delayMs(500);
		LCD_data('H');			// write the world
		delayMs(1);
		LCD_data('e');			
		delayMs(1);
		LCD_data('l');			
		delayMs(1);
		LCD_data('l');			
		delayMs(1);
		LCD_data('o');	
		delayMs(500);		
	}
	
	return 0;
}