# Name: Makefile
# Author: Daniel Salinas
# Copyright: Daniel Salinas (2009)
# License: GPL v3

##################
# Device Section #
##################
DEVICE = attiny861
AVRDUDE_DEVICE = t861
CLOCK = 16000000

###################
# Library Section #
###################
AVRLIB = /opt/libs/avrlib

# Use the LDFLAGS with "pololu" if doing
# 3pi development or if you just want to
# use the 3pi libraries.
LDFLAGS = -Wl,-gc-sections -Wl,-relax
#LDFLAGS = -Wl,-gc-sections -lpololu_$(DEVICE) -Wl,-relax


######################
# Programmer Section #
######################
PROGRAMMER = usbtiny
PORT = usb
FUSES = -U lfuse:w:0xef:m -U hfuse:w:0xd5:m
AVRDUDE = avrdude -c $(PROGRAMMER) -P $(PORT) -p $(AVRDUDE_DEVICE)

####################
# Compiler Section #
####################
CFLAGS = -g -Wall -mcall-prologues -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -Os -I. -I$(shell cd ${AVRLIB}; pwd) #-I$(shell cd ${AVRLIB}/conf; pwd)
CPP = avr-g++
CC = avr-gcc
OBJ2HEX = avr-objcopy
TARGET = main
OBJECTS = $(TARGET).o

# symbolic targets:
all:	$(TARGET).hex

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(CC) $(CFLAGS) -S $< -o $@

#################################
# Non-3pi development section   #
# Comment out if working on the #
# 3pi robotics development      #
# platform.                     #
#################################
main.elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	$(OBJ2HEX) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
#######################
# End non-3pi section #
#######################

disasm: main.elf
	$(OBJ2HEX) -d main.elf

cpp:
	$(CPP) $(CFLAGS) -E main.c

clean:
	rm -f *.o *.hex *.obj *.elf $(OBJECTS)

###############################
# 3pi development section     #
# Comment out if working on   #
# general AVR develpment,     #
# especially if you are doing #
# V-USB development.          #
###############################
#%.hex: %.obj
#	$(OBJ2HEX) -R .eeprom -O ihex $< $@

#%.obj: %.o
#	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@
###################
# End 3pi section #
###################

flash:	all
	$(AVRDUDE) -U flash:w:$(TARGET).hex

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash

# Since we don't want to ship the driver multiple times, we copy it into this project:
usbdrv:
	cp -r $(VUSBLIB)/usbdrv .