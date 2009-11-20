#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRD |= 1 << PD3;
    DDRD |= 1 << PD4;
    while(1) {
        PORTD |= 1 << PD3;
        _delay_ms(25);
        PORTD &= 0 << PD3;
        _delay_ms(25);

        PORTD |= 1 << PD4;
        _delay_ms(25);
        PORTD &= 0 << PD4;
        _delay_ms(25);
    }
    return 0;
}
