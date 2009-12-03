/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>			// default
#include <avr/interrupt.h>	// for sei()
#include <avr/pgmspace.h>	// required by usbdrv.h
#include <avr/wdt.h>		// Needed for usb stuffs
#include <util/delay.h>		// for _delay_ms()

#include "usbdrv.h"

void ledOn()
{
	PORTD |= 1 << PD3;
}

void ledOff()
{
	PORTD &= 0 << PD3;
}

uchar usbFunctionSetup(uchar data[8])
{
	switch (data[1])
	{
		case 0:
			ledOn();
			break;
		case 1:
			ledOff();
			break;
		default:
			break;
	}
	return 0;
}

int main(void)
{	
	PORTD = 0;
	DDRD |= 1 << PD3;
	DDRD &= 0 << PD2;
	DDRD &= 0 << PD5;
	
	wdt_enable(WDTO_1S);
	
	usbInit();
	usbDeviceDisconnect();
	
	_delay_ms(250);
	
	usbDeviceConnect();
	sei();
	
    for(;;){
		wdt_reset();
		usbPoll();
    }
    return 0;
}
