#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "eyes.h"

void eyes_init()
{
	DDRB |= _BV(GPIO_EYES);
}

void set_eyes(uint8_t cmd)
{
	switch (cmd) {
		case EYES_OFF:
			PORTB &= ~_BV(GPIO_EYES);
			break;

		case EYES_ON:
			PORTB |= _BV(GPIO_EYES);
			break;

	}
}

uint8_t get_eyes(void)
{
	if (PORTB & _BV(GPIO_EYES))
		return EYES_ON;
	else
		return EYES_OFF;
}
