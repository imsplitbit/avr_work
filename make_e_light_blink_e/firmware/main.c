#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= 1<<PB0; /* set PB0 to output */
    while(1) {
        PORTB &= ~(1<<PB0); /* LED on */
        _delay_ms(500);
        PORTB |= 1<<PB0; /* LED off */
        _delay_ms(500);
    }
    return 0;
}
