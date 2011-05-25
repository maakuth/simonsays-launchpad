/* Some TI LaunchPad utility functions */
#ifndef __MSP430G2231
#include "msp430g2231.h"
#endif

/*Toggles leds, 0=green, 1=red*/
void toggle_led(int led)
{
  if (led == 0)
  {
    P1OUT ^= 0x40; // Toggle LED1
    return;
  }

  /* Else, toggle the other one */
  P1OUT ^= 0x01; // Toggle LED2
}

/* Lights or dims leds, 
 * led: 0=green, 1=red, 
 * value: 0=off, 1=on */
void set_led(int led, int value)
{
	if (led == 0)
	{
		if (value) 
		{ 
			P1OUT |= 0x40;
		}
		else
		{
			P1OUT &= ~0x40;
		}
		return;
	}
	
	if (value) 
	{ 
		P1OUT |= 0x01;
	}
	else
	{
		P1OUT &= ~0x01;
	}
}

/* Set the hardware in state we need to run properly */
void hw_init()
{
   WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

   P1DIR |= (LED0 + LED1); //Set P1 to output mode for LEDs

   P1IES |= BUTTON; // trigger P1.3 when line goes from high to low
   P1IFG &= ~BUTTON; // P1.3 Clear IFG
   P1IE |= BUTTON; // Enable interrupt for P1.3 (push button on LaunchPad board)
   __enable_interrupt();
}
