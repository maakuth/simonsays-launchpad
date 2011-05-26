/**
 * Simon Says for TI MSP430G2231 microcontroller
 * Markus Vuorio <markus.vuorio@jyu.fi>
 * Spring 2011 for JYU claoh 2010 course
 *
 * Pattern definitions
 * */

#include "launchpadutils.h"
#define PATTERN_COUNT 2 /* Amount of patterns - 1 */
#define PATTERN_LENGTH 9 /* How long can patterns be */

/* Pad with zeros to fit PATTERN_HEIGHT, last one must be PATTERN_END (==0) */
int patterns[][PATTERN_LENGTH] = {
	{100, 100, 100, PATTERN_END, 0, 0, 0, 0, 0},
	{100, 100, 100, 100, 100, PATTERN_END, 0, 0, 0},
 	{100, 50, 100, 200, 100, 50, 100, PATTERN_END, 0}
};
