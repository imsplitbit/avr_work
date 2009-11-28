/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <util/delay.h>
#include "usbdrv.h"

#define CMD_READ_VERSION   		0x00 // first attempt is to handle a version request
#define VENDOR_RQ_WRITE_BUFFER 	0x00
#define VENDOR_RQ_READ_BUFFER  	0x01

static uchar currentPosition;
static uchar bytesRemaining; 

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
    usbRequest_t    *rq = (void *)data;
    usbMsgLen_t len;

    switch(rq->bRequest) {
    case VENDOR_RQ_WRITE_BUFFER:
        currentPosition = 0;                // initialize position index
        bytesRemaining = rq->wLength.word;  // store the amount of data requested
        if(bytesRemaining > sizeof(buffer)) // limit to buffer size
            bytesRemaining = sizeof(buffer);
        return USB_NO_MSG;                  // tell driver to use usbFunctionWrite()

    case VENDOR_RQ_READ_BUFFER:
		currentPosition = 0;                // initialize the position index
		bytesRemaining = rq->wLength.word;  // store the amount of data requested
		return USB_NO_MSG;
    }

    return 0;   /* default for not implemented requests: return no data back to host */
}

/* usbFunctionRead() is called when the host requests a chunk of data from
 * the device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar   usbFunctionRead(uchar *data, uchar len)
{
    if(len > bytesRemaining)
        len = bytesRemaining;
    eeprom_read_block(data, (uchar *)0 + currentAddress, len);
    currentAddress += len;
    bytesRemaining -= len;
    return len;
}

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar   usbFunctionWrite(uchar *data, uchar len)
{
    if(bytesRemaining == 0)
        return 1;               /* end of transfer */
    if(len > bytesRemaining)
        len = bytesRemaining;
    eeprom_write_block(data, (uchar *)0 + currentAddress, len);
    currentAddress += len;
    bytesRemaining -= len;
    return bytesRemaining == 0; /* return 1 if this was the last chunk */
}

int main(void)
{
	DDRB |= 1 << PB0;
	
    for(;;){
        /* insert your main loop code here */
    }
    return 0;
}
