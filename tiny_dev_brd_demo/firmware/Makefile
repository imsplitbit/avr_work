# Name: Makefile
# Author: Daniel Salinas
# Copyright: Daniel Salinas (2009)
# License: GPL v3

##################
# Device Section #
##################
DEVICE = attiny2313
AVRDUDE_DEVICE = t2313
CLOCK = 20000000

###################
# Library Section #
###################
AVRLIB = /opt/libs/avrlib
VUSBLIB = /opt/libs/vusb-20090822
LDFLAGS = -Wl,-gc-sections -Wl,-relax

######################
# Programmer Section #
######################
PROGRAMMER = avrisp2
PORT = usb
FUSES = -U lfuse:w:0xee:m -U hfuse:w:0xdb:m -U efuse:w:0xff:m
AVRDUDE = avrdude -c $(PROGRAMMER) -P $(PORT) -p $(AVRDUDE_DEVICE)

####################
# Compiler Section #
####################
OBJECTS = main.o
CFLAGS = -g -Wall -mcall-prologues -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -Os -I$(shell cd ${AVRLIB}; pwd)
CPP = avr-g++
CC = avr-gcc
OBJ2HEX = avr-objcopy
TARGET = main
OBJECTS = usbdrv/usbdrv.obj usbdrv/usbdrvasm.obj usbdrv/oddebug.obj
# symbolic targets:
all:	$(TARGET).hex

clean:
	rm -f *.o *.hex *.obj

%.hex: %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

%.obj: %.o
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(TARGET).hex

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash

# Since we don't want to ship the driver multiple times, we copy it into this project:
usbdrv:
	cp -r $(VUSBLIB)/usbdrv .