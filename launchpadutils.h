#ifndef LAUNCHPADUTILS_H_
#define LAUNCHPADUTILS_H_
#endif /*LAUNCHPADUTILS_H_*/

#define LED0 BIT0
#define LED1 BIT6
#define BUTTON BIT3

#define ERROR_TOLERANCE 1000 /* How much can player miss? */
#define	SLEEP_UNIT 1000 /* How long is the sleep loop? */

/* Game states */
#define STATE_INIT 0   /* Initial state aftet startup */   
#define STATE_SHOW 1   /* Showing lightshow */
#define STATE_INPUT 2  /* Waiting for player input */
#define STATE_OVER 3	 /* Game over */

/* Simple definitions to clarify code */
#define BUTTON_PRESSED 1
#define BUTTON_NOT_PRESSED 0

#define LED_GREEN 0
#define LED_RED 1

#define LED_OFF 0
#define LED_ON 1

#define MASK_GREEN 0x40
#define MASK_RED 0x01

#define PATTERN_END 0

void toggle_led(int led);
void set_led(int led, int value);
void hw_init();