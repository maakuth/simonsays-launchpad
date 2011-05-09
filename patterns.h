/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 *
 * Pattern definitions
 * */

#define PATTERN_COUNT 2 /* Amount of patterns - 1 */
int *patterns = {
	{100, 50, 100, 50, 100, 50, 0},
 	{100, 50, 100, 200, 100, 50, 100, 0},
 	{100, 50, 100, 50, 100, 50, 200, 50, 200, 50, 0}
};