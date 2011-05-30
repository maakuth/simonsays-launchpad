/* Some TI LaunchPad utility functions */
#include <msp430g2231.h>
#include "launchpadutils.h"

/*Toggles leds, LED_GREEN or LED_RED */
void toggle_led(int led)
{
  if (led == LED_GREEN)
  {
    P1OUT ^= MASK_GREEN; // Toggle green led
    return;
  }

  /* Else, toggle the other one */
  P1OUT ^= MASK_RED; // Toggle red led
}

/* Lights or dims leds, 
 * led: LED_GREEN or LED_RED 
 * value: LED_ON or LED_OFF */
void set_led(int led, int value)
{
	if (led == LED_GREEN)
	{
		if (value) 
		{ 
			P1OUT |= MASK_GREEN;
		}
		else
		{
			P1OUT &= ~MASK_GREEN;
		}
		return;
	}
	
	/* We will get here only when we get LED_RED */
	if (value) 
	{ 
		P1OUT |= MASK_RED;
	}
	else
	{
		P1OUT &= ~MASK_RED;
	}
}

/* Set the hardware in state we need to run properly */
void hw_init()
{
   WDTCTL = WDTPW + WDTHOLD; /* Stop watchdog timer */

   P1DIR |= (LED0 + LED1); /* Set P1 to output mode for LEDs */
   BCSCTL3 |= LFXT1S_2; /* Select internal VLO as clock */
   P1IES |= BUTTON; /* trigger P1.3 when line goes from high to low */
   P1IFG &= ~BUTTON; /* P1.3 clear interrupt flag */
   P1IE |= BUTTON; /* Enable interrupt for P1.3 (push button on LaunchPad board) */
   TACCTL0 |= CCIE; /* Enable timer interrupt */
   TACCR0 = SLEEP_UNIT; /* Set sleep time */
   TACTL = TASSEL_1 | MC_1; /* Configure Timer A and start it */
   __enable_interrupt();
   
}
