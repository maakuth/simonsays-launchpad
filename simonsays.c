/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 *
 * Main program
 * */
#include "msp430g2231.h"
#include "patterns.h"

#define ERROR_TOLERANCE 1000 /*How much can player miss*/
#define ALLOW_NEGATIVE 1 /*Is it ok reverse the pattern?*/

/*Blinks leds in rhythm pattern specified by *pattern so that
  even array slots are led on and odd are led off. End with zero.
  Example:
  {100, 50, 100, 200, 100, 50, 100, 0}*/
void showpattern(int *pattern)
{

}

/*Call this when key pressed*/
void key_down()

/*Call this when key released*/
void key_release()

/*Toggles leds, 0=green, 1=red*/
void toggle_led(int led)



void sleep(int time)
{

}

void main()
{
	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
	
	P1DIR |= 0x01; //Set P1.0 (LED1) to output
	P1DIR |= 0x40; //Set P1.6 (LED2) to output as well 
	
	volatile unsigned int i =0;
	P1OUT ^= 0x01;
	
	for(;;) 
	{
		P1OUT ^= 0x01;
		P1OUT ^= 0x40;
		
		i = 50000;
		do (i--);
		while (i!=0);
	}
}
