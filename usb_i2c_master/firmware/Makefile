# Name: Makefile
# Author: Daniel Salinas
# Copyright: Daniel Salinas (2009)
# License: GPL v3

DEVICE     	= attiny2313
CLOCK      	= 20000000
AVRLIB	   	= /opt/libs/avrlib
VUSBLIB	   	= /opt/libs/vusb-20090822
PROGRAMMER 	= -c avrisp2 -P usb -p t2313 
FUSES      	= -U lfuse:w:0xee:m -U hfuse:w:0xdb:m -U efuse:w:0xff:m
CFLAGS		= -Iusbdrv -I. -I$(shell cd ${AVRLIB}; pwd)
AVRDUDE 	= avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE 	= avr-gcc -Wall -Os -DF_CPU=$(CLOCK) $(CFLAGS) -mmcu=$(DEVICE)
OBJECTS 	= usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o main.o

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Since we don't want to ship the driver multipe times, we copy it into this project:
usbdrv:
	cp -r $(VUSBLIB)/usbdrv .

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
