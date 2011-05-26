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

int button_pressed = 0; /* What is the button state? Zero this when done */
int state = 0;  /* Game states, see STATE_s */
int *pattern; /* Pattern that we are showing / was last shown */
int lastpattern = 0; /* Last pattern index */
int pattern_counter, timer_counter; /* Global counters, ouch! */
int fail = 0; /* How many errors has the player made */

/* Blinks leds in rhythm pattern specified by *pattern so that
 * even array slots are led on and odd are led off. End with zero.
 * Example:
 * {100, 50, 100, 200, 100, 50, 100, 0} */
void show_pattern(int *pattern_)
{
  pattern = pattern_;
  pattern_counter = 0;
  timer_counter = 0;
  state = STATE_SHOW;
  set_led(LED_RED, LED_ON); /* Let's light the red led to tell show is on */
}

/* Starts the game, duh! */
void start_game()
{
  pattern_counter = 0;
  timer_counter = 0;
  fail = 0;
  set_led(LED_GREEN, LED_OFF); /* Set leds so we now what's happening */
  set_led(LED_RED, LED_ON); 
  state = STATE_INPUT;
}

/**
 * Select a pattern
 */
int* get_pattern()
{
	/* TODO: Instead of stored patterns, these could be generated */
	if (++lastpattern > PATTERN_COUNT)
	{
		lastpattern = 0;
	}
	
	return patterns[lastpattern];
}

/* Sleep for time microfortnights or what have you 
 * TODO: There's a timer on chip, it should be utilised */
void mysleep(int time)
{
  volatile unsigned int i =0;

  i = time * SLEEP_UNIT;
  do (i--);
  while (i!=0 && button_pressed == BUTTON_NOT_PRESSED);
}

/* This is called when pattern was done */
void game_over()
{
	state = STATE_OVER;
	if (fail == 0)
	{
		set_led(LED_GREEN, LED_ON); /* Light the green led and dim the red one */
		set_led(LED_RED, LED_OFF); /* as the player has won */
	}
	else
	{
		set_led(LED_RED, LED_ON); /* Vice versa */
		set_led(LED_GREEN, LED_OFF);
		mysleep(100); /* Sleep a while to ensure player gets the message */
		set_led(LED_GREEN, LED_ON); /* Back to the starting point */
	}
}

/* Main loop body during the game input sequence, after
 * the lights have flashed */
void input_loop()
{
  /* See if button state has changed */
  if ( button_pressed ) 
  {
    if (pattern[pattern_counter] - timer_counter < ERROR_TOLERANCE || 
        timer_counter - pattern[pattern_counter] < ERROR_TOLERANCE)
    {
    	/* No problem */
    }
    else fail++;
    
    pattern_counter++;
    timer_counter = 0;
    
    if (pattern[pattern_counter] == PATTERN_END)
    {
    	game_over();
    }
  }
  else
  {
  	timer_counter++; /* In input mode, we use timer_counter to time button press */
  }
  button_pressed = 0;
}

/* Main loop body during light show */
void show_loop()
{
	/* We use pattern_counter to keep track of progress of the light pattern
	 * and timer_counter to time individual light blinks. */
	timer_counter++;
	if (timer_counter >= pattern[pattern_counter])
	{
    	pattern_counter++;
    	timer_counter = 0;
    	toggle_led(LED_GREEN);
    	
    	/* Let's end the show when we get zero */
    	if (pattern[pattern_counter] == 0)
    	{
    		start_game();
    		set_led(LED_GREEN, LED_OFF); /* Dim both of the leds  */
    		set_led(LED_RED, LED_OFF); /* to signal end of show */
    	}
	}	
}

int main()
{
  hw_init();
  set_led(LED_GREEN, LED_ON);
  int extrasleep = 0; /* Should we sleep more besides the default one unit */

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
      	toggle_led(LED_GREEN); /* Let's blink the green one to show we're ready */
      }
      if ( button_pressed ) 
      {
      	int *pattern_ = get_pattern();
        show_pattern(pattern_); /* Begin lightshow */
      }
      extrasleep = 10; /* Additional sleep to keep led flash visible */
    }
    button_pressed = BUTTON_NOT_PRESSED;
    mysleep(1 + extrasleep);
    extrasleep = 0;
  }
  return 0;
}

/* Port 1 interrupt service routine */
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	P1IFG &= ~BUTTON; /* P1.3 interrupt flag cleared */
	P1IES ^= BUTTON; /* Toggle the interrupt edge */
	button_pressed = BUTTON_PRESSED;
}
