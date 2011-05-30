#Simon Says for MSP430 Makefile for msp430-gcc tools
#Heavily influenced by http://www.ruuvipenkki.fi/2010/10/23/launchpad-kehitysymparisto-linuxissa
TARGET=simon_says

CC=/opt/msp430-gcc-4.4.5/bin/msp430-gcc
LD=/opt/msp430-gcc-4.4.5/bin/msp430-ld
SIZE=/opt/msp430-gcc-4.4.5/bin/msp430-size
STRIP=/opt/msp430-gcc-4.4.5/bin/msp430-strip

CFLAGS=-Os -Wall -g -mmcu=msp430x2231 -ffunction-sections -fdata-sections -fno-inline-small-functions

LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--relax
LDFLAGS += -Wl,--gc-sections

OBJS=launchpadutils.o simonsays.o

all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJS) $(LDFLAGS)
	#$(STRIP) $(TARGET).elf
	$(SIZE) --format=sysv $(TARGET).elf

program: $(TARGET).elf
	mspdebug rf2500 "prog $(TARGET).elf"

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(TARGET).elf $(OBJS) $(TARGET).map
