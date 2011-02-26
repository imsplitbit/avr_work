/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "usbdrv.h"

#define CMD_READ_VERSION        0x00 // first attempt is to handle a version request                                    
#define VENDOR_RQ_WRITE_BUFFER  0x00
#define VENDOR_RQ_READ_BUFFER   0x01

typedef signed char int8;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

static uchar buffer[64];
static uint8_t buffer_len;
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
            
            /* I stole this from Ron Pedde */
        case VENDOR_RQ_READ_BUFFER:
            len = 64;                           // we return up to 64 bytes                                                 
            if(len > rq->wLength.word)          // if the host requests less than we have                                   
                len = rq->wLength.word;         // return only the amount requested                                         
            usbMsgPtr = buffer;                 // tell driver where the buffer starts                                      
            return len;                         // tell driver how many bytes to send                                       
    }
    
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* usbFunctionWrite() is called when the host sends a chunk of data to the                                              
 * device. For more information see the documentation in usbdrv/usbdrv.h.                                               
 */
uchar usbFunctionWrite(uchar *data, uchar len)
{
    uchar i;
    
    if(len > bytesRemaining)                // if this is the last incomplete chunk                                     
        len = bytesRemaining;               // limit to the amount we can store                                         
    bytesRemaining -= len;
    for(i = 0; i < len; i++)
        buffer[currentPosition++] = data[i];
    
    if(bytesRemaining == 0) {
        switch(buffer[0]) {
            case CMD_READ_VERSION:
                buffer[0] = 2;
                buffer[1] = 0;
                buffer_len = 2;
                break;
        }
    }
    return bytesRemaining == 0;             // return 1 if we have all data                                             
}

int main(void)
{
    DDRA |= 1 << PA0;
    
    uchar i;
    
    wdt_enable(WDTO_1S);
    wdt_disable();
    
    usbInit();
    
    usbDeviceDisconnect();
    
    i = 0;
    while(--i){
        wdt_reset();
        _delay_ms(1);
    }
    
    _delay_ms(250);
    usbDeviceConnect();
    sei();
    
    while(1){
        PORTA |= 1 << PA0;
        _delay_ms(100);
        PORTA &= 0 << PA0;
        _delay_ms(100);
        wdt_reset();                                                                                                  
        usbPoll();
    }
    return 0;
}
