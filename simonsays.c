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

int button_state = 0;  /* What was the button state last time */
int state = 0;  /* Game state: 0 = Initial 1 = Light show 2 = Player input */
int *lastpattern; /* Pattern that was last shown */

/*Blinks leds in rhythm pattern specified by *pattern so that
  even array slots are led on and odd are led off. End with zero.
  Example:
  {100, 50, 100, 200, 100, 50, 100, 0}*/
void showpattern(int *pattern)
{

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
        game_running = 1; 
      }
    }
    button_state = button_state_now;
    sleep(1);
  }
}
