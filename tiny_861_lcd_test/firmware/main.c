// LCD Test
// ATTiny861

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcd.c"

int main(void) {
    //int i=0;
    DDRA |= (1 << 3); // Set port 3 to output

    // Begin infinite loop
    /* while(1) { */
/*         PORTA |= (1 << 3); // Set port A3 high */
/*         _delay_ms(100); */
/*         PORTA &= (0 << 3); // Set port A3 low */
/*         _delay_ms(100); */
/*     } */
    lcd_init(LCD_DISP_ON);
    lcd_clrscr();
    lcd_puts("ATTiny 861");
    lcd_newline(2);
    lcd_puts("LCD TEST");
    _delay_ms(5000);
    lcd_clrscr();
    while(1) {
        PORTA |= (1 << 3); // Set port A3 high
        lcd_clrscr();
        lcd_puts("THIS IS ONLY");
        _delay_ms(500);
        PORTA &= (0 << 3); // Set port A3 low
        lcd_newline(2);
        lcd_puts("A TEST");
        _delay_ms(500);
    }
    exit(0);
}
