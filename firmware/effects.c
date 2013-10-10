/*
 *  iron-man-helmet-controller
 *  Copyright (C) 2013 Roman Moravcik
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <util/delay.h>

#include "common.h"
#include "effects.h"

enum {
	FADE_IN = 0,
	FADE_OUT
};

static void effect_blink(uint8_t gpio);
static void effect_fade_effect(uint8_t gpio, uint8_t mode);

void effect_init(uint8_t gpio)
{
	DDRB |= _BV(gpio);
}

void effect_set_mode(uint8_t gpio, uint8_t mode)
{
	switch (mode) {
		case MODE_OFF:
			PORTB &= ~_BV(gpio);
			break;

		case MODE_ON:
			PORTB |= _BV(gpio);
			break;

		case MODE_BLINK:
			effect_blink(gpio);
			break;

		case MODE_FADE_IN:
			effect_fade_effect(gpio, FADE_IN);
			break;

		case MODE_FADE_OUT:
			effect_fade_effect(gpio, FADE_OUT);
			break;
	}
}

// takes 200ms
static void effect_blink(uint8_t gpio)
{
	PORTB &= ~_BV(gpio);
	_delay_ms(50);
	PORTB |= _BV(gpio);
	_delay_ms(50);
	PORTB &= ~_BV(gpio);
	_delay_ms(50);
	PORTB |= _BV(gpio);
	_delay_ms(50);
}

// takes 3000ms
static void effect_fade_effect(uint8_t gpio, uint8_t mode)
{
	uint8_t step, i = 0;
	uint8_t time, off_time, on_time;

	// fade-in in 50 steps
	for (step = 0; step <= 50; step++) {
		// calculate on/off times for a signal with period 1kHz
		if (mode == FADE_IN) {
			on_time = 2 * step;
			off_time = 100 - on_time;
		} else {
			off_time = 2 * step;
			on_time = 100 - off_time;
		}

		// remain 30 ms on each step
		for (i = 0; i < 30; i++) {
			PORTB &= ~_BV(gpio);

			for (time = 0; time < off_time; time++) {
				_delay_us(20);
			}

			PORTB |= _BV(gpio);

			for (time = 0; time < on_time; time++) {
				_delay_us(20);
			}
		}
	}
}
