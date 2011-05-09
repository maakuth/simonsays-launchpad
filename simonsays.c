/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 *
 * Main program
 * */
#include "msp430g2231.h"
#include "patterns.h"

#define ERROR_TOLERANCE 1000 /* How much can player miss? */
#define ALLOW_NEGATIVE 1 /* Is it ok reverse the pattern? */

/* Game states */
#define STATE_INIT 0   /* Initial state aftet startup */   
#define STATE_SHOW 1   /* Showing lightshow */
#define STATE_INPUT 2  /* Waiting for player input */

int button_state = 0;  /* What was the button state last time */
int state = 0;  /* Game states, see STATE_s */
int *pattern; /* Pattern that we are showing / was last shown */
int i, j; /* Global counters, ouch! */

/*Blinks leds in rhythm pattern specified by *pattern so that
  even array slots are led on and odd are led off. End with zero.
  Example:
  {100, 50, 100, 200, 100, 50, 100, 0}*/
void show_pattern(int *pattern_)
{
  *pattern = *pattern_;
  i = 0;
  j = 0;
  state = STATE_SHOW;
}


/*Call this when button pressed*/
void button_down()

/*Call this when button released*/
void button_release()

/*Toggles leds, 0=green, 1=red*/
void toggle_led(int led)
{
  if (led == 0)
  {
    P1OUT ^= 0x01; // Toggle LED1
    return;
  }

  /* Else, toggle the other one */
  P1OUT ^= 0x40; // Toggle LED2
}

/* Sleep for time microfortnights or what have you */
void sleep(int time)
{
  volatile unsigned int i =0;

  i = time * 10000;
  do (i--);
  while (i!=0);
}

/* Set the hardware in state we need to run properly */
void hw_init()
{
   WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

   P1DIR |= 0x01; //Set P1.0 (LED1) to output mode
   P1DIR |= 0x40; //Set P1.6 (LED2) to output mode as well
}

/* Main loop body during the game */
void input_loop()
{
  /* See if button state has changed */
  if ( button_state_now != button_state ) 
  {
    if (button_state_now != STATE_DOWN) button_down();
    else button_release();
  }
  
  if (
}

/* Main loop body during light show */
void show_loop()
{
	/* We use i to keep track of progress of the light pattern
	 * and j to time individual light blinks. */
	j++;
	if (j >= pattern[i])
	{
    	i++;
    	j = 0;
    	toggle_led(0);
    	
    	/* Let's end the show when we get zero */
    	if (pattern[i] == 0)
    	{
    		// TODO: Should we signal ending of the show
    		state = STATE_INPUT;
    	}
	}	
}

void main()
{
  hw_init();	

  /* Main loop */
  for(;;) 
  {
    if (state == 2)
    {
      input_loop();
    }
    if (state == 1)
    {
      show_loop();
    }
    else 
    {
      /* Button press starts the game */
      //TODO: Maybe some light activity to tell we are ready
      if ( button_state_now != button_state ) 
      {
        show_pattern(x); //TODO: Get pattern somewhere
      }
    }
    button_state = button_state_now;
    sleep(1);
  }
}
