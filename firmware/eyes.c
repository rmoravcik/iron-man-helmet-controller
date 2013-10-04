#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "eyes.h"

enum {
	FADE_IN = 0,
	FADE_OUT
};

static void eyes_blink(void);
static void eyes_fade_effect(uint8_t mode);

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

		case EYES_BLINK:
			eyes_blink();
			break;

		case EYES_FADE_IN:
			eyes_fade_effect(FADE_IN);
			break;

		case EYES_FADE_OUT:
			eyes_fade_effect(FADE_OUT);
			break;
	}
}

static void eyes_blink(void)
{
	PORTB &= ~_BV(GPIO_EYES);
	_delay_ms(50);
	PORTB |= _BV(GPIO_EYES);
	_delay_ms(50);
	PORTB &= ~_BV(GPIO_EYES);
	_delay_ms(50);
	PORTB |= _BV(GPIO_EYES);
	_delay_ms(50);
}

static void eyes_fade_effect(uint8_t mode)
{
	uint8_t step, i = 0;
	uint8_t time, off_time, on_time;

	// fade in eyes in 50 steps
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
			PORTB &= ~_BV(GPIO_EYES);

			for (time = 0; time < off_time; time++) {
				_delay_us(20);
			}

			PORTB |= _BV(GPIO_EYES);

			for (time = 0; time < on_time; time++) {
				_delay_us(20);
			}
		}
	}
}
