/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 *
 * Main program
 * */
#include "msp430g2231.h"
#include "patterns.h"
#include "launchpadutils.h"

#define LED0 BIT0
#define LED1 BIT6
#define BUTTON BIT3

#define ERROR_TOLERANCE 1000 /* How much can player miss? */
#define	SLEEP_TIME 5000 /* How long is the sleep loop? */

/* Game states */
#define STATE_INIT 0   /* Initial state aftet startup */   
#define STATE_SHOW 1   /* Showing lightshow */
#define STATE_INPUT 2  /* Waiting for player input */
#define STATE_OVER 3	 /* Game over */

int button_state_now = 0; //What is the button state? Zero this when done
int state = 0;  /* Game states, see STATE_s */
int *pattern; /* Pattern that we are showing / was last shown */
int lastpattern = 0; /* Last pattern index */
int i, j; /* Global counters, ouch! */
int fail = 0; /* How many errors has the player made */

/*Blinks leds in rhythm pattern specified by *pattern so that
  even array slots are led on and odd are led off. End with zero.
  Example:
  {100, 50, 100, 200, 100, 50, 100, 0}*/
void show_pattern(int *pattern_)
{
  pattern = pattern_;
  i = 0;
  j = 0;
  state = STATE_SHOW;
  set_led(1, 1); /* Let's light the red led to tell show is on */
}

/* Starts the game, duh! */
void start_game()
{
  i = 0;
  j = 0;
  fail = 0;
  state = STATE_INPUT;
}

/**
 * Select a pattern
 */
int* get_pattern()
{
	if (++lastpattern > PATTERN_COUNT)
	{
		lastpattern = 0;
	}
	volatile int z, iz;
	
	return patterns[lastpattern];
}

/* Sleep for time microfortnights or what have you */
void sleep(int time)
{
  volatile unsigned int i =0;

  i = time * SLEEP_TIME;
  do (i--);
  while (i!=0);
}

/* This is called when pattern was done */
void game_over()
{
	state = STATE_OVER;
	if (fail == 0)
	{
		set_led(0, 1);
	}
	else
	{
		set_led(1, 1);
	}
}

/* Main loop body during the game input sequence, after
 * the lights have flashed */
void input_loop()
{
  /* See if button state has changed */
  if ( button_state_now ) 
  {
    if (pattern[i] - j < ERROR_TOLERANCE || j - pattern[i] < ERROR_TOLERANCE)
    {
    	/* No problem */
    }
    else fail++;
    
    i++;
    j = 0;
    
    if (pattern[i] == 0)
    {
    	int jaa = pattern[i];
    	game_over();
    }
  }
  else
  {
  	j++; /* In input mode, we use j-counter to time button press */
  }
  button_state_now = 0;
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
    		start_game();
    		set_led(1, 0); /* Dim the red led to signal end of show */
    	}
	}	
}

void main()
{
  hw_init();
  set_led(0,1);	

  /* Main loop */
  for(;;) 
  {
    if (state == STATE_INPUT)
    {
      input_loop();
    }
    else if (state == STATE_SHOW)
    {
      show_loop();
    }
    else 
    {
      /* Button press starts the game */
      if (state != STATE_OVER)
      {
      	toggle_led(0); /* Let's blink the green one to show we're ready */
      }
      if ( button_state_now ) 
      {
      	int *pattern_ = get_pattern();
        show_pattern(pattern_); /* Begin lightshow */
      }
    }
    button_state_now = 0;
    sleep(1);
  }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	//P1OUT ^= 0x01; // P1.0 = toggle
	P1IFG &= ~BUTTON; // P1.3 IFG cleared
	P1IES ^= BUTTON; // Toggle the interrupt edge
	button_state_now = 1;
}
