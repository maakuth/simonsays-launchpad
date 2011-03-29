#include  "msp430g2231.h"
/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 * */

void main()
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
	
	P1DIR |= 0x01; //Set P1.0 (LED1) to output
	P1DIR |= 0x40; //Set P1.6 (LED2) to output as well 
	
	volatile unsigned int i =0;
	
	for(;;) 
	{
		P1OUT ^= 0x01;
		P1OUT ^= 0x40;
		
		i = 50000;
		do (i--);
		while (i!=0);
	}
}
