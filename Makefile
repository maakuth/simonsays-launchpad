#Simon Says for MSP430 Makefile for msp430-gcc tools
CC=/opt/msp430-gcc-4.4.5/bin/msp430-gcc
LD=/opt/msp430-gcc-4.4.5/bin/msp430-ld
CFLAGS=-Os

simonsays: launchpadutils.c simonsays.c

clean: 
	rm simonsays
