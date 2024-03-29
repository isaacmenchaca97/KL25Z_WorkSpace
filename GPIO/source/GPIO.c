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
		LCD_data('H');			// write the world
		LCD_data('e');			
		LCD_data('l');			
		LCD_data('l');			
		LCD_data('o');	
		delayMs(500);		
	}
	
	return 0;
}