#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#define F_CPU 20000

uint16_t i;
uint8_t debounce_counter = 0;
unsigned char old_value;
unsigned char new_value;

unsigned char debouncer(unsigned char pinmask) {
	old_value = PINB & pinmask;
	while(debounce_counter < 20) {
		new_value = PINB & pinmask;
		
		if(new_value == old_value) {
			debounce_counter++;
		} else {
			debounce_counter = 0;
			old_value = new_value;
		};
		_delay_ms(20);
	};
	return old_value;
}

void bottom() {
	PORTD |= 1 << PD6;
	_delay_ms(1000);
	PORTD &= 0 << PD6;
	_delay_ms(500);
}

void middle() {
	PORTD |= 1 << PD6;
	_delay_ms(1500);
	PORTD &= 0 << PD6;
	_delay_ms(500);
}

void top() {
	PORTD |= 1 << PD6;
	_delay_ms(2000);
	PORTD &= 0 << PD6;
	_delay_ms(500);
}

int main() {
	DDRD |= 1 << PD6; /* servo output pin */
	DDRB &= 0 << PB0; /* bottom servo movement */
	DDRB &= 0 << PB1; /* middle servo movement */
	DDRB &= 0 << PB2; /* top servo movement */

	while(1) {
				
		if(debouncer(0x01) == 0x01) {
			while(debouncer(0x01) == 0x01) {
				bottom();
			};
		};
		if(debouncer(0x02) == 0x02) {
			while(debouncer(0x02) == 0x02) {
				middle();
			};
		};
		if(debouncer(0x04) == 0x04) {
			while(debouncer(0x04) == 0x04) {
				top();
			};
		};
		_delay_ms(500);
	};

	return 0;
};
