/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <util/delay.h>
#include "i2cmaster.h"

#define LOCAL_ADDR 0x00
#define TARGET_ADDR 0x01

int main(void) {
    unsigned char ret;
    
    i2c_init();
    
    ret = i2c_start(TARGET_ADDR + I2C_WRITE);
    if(ret) {
        i2c_stop();
    } else {
        while(1) {
            i2c_write(0x40);
            i2c_write(0x44);
            _delay_ms(500);
        }a
    }
    while(1) {
    }
    return 0;   /* never reached */
}

