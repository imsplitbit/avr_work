/* Name: main.c
 * Author: Daniel Salinas
 * Copyright: Daniel Salinas (2009)
 * License: GPL v3
 */

#include <avr/io.h>
#include <util/delay.h>

int main()
{
    DDRB |= (1 << PB0);
    while (1) {
        PORTB |= (1 << PB0);
        _delay_us(300);
        PORTB &= (0 << PB0);
        _delay_us(700);
    };
    return 0;   /* never reached */
}
