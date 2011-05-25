/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 *
 * Pattern definitions
 * */

#define PATTERN_COUNT 1 /* Amount of patterns - 1 */

/* Pad with zeros */
int patterns[][9] = {
	{100, 100, 100, 0, 0, 0, 0, 0, 0},
	{100, 50, 100, 50, 100, 50, 0, 0, 0},
 	{100, 50, 100, 200, 100, 50, 100, 0, 0}
};
