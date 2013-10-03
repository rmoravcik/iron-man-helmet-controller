#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "voice.h"

static void voice_send(int command);

void voice_init(void)
{
//	DDRD |= _BV(GPIO_WT588_RESET) | _BV(GPIO_WT588_DATA);
	DDRD |= _BV(GPIO_WT588_DATA);
//	DDRD &= ~_BV(GPIO_WT588_BUSY);
	DDRD &= ~(_BV(GPIO_WT588_BUSY) | _BV(GPIO_WT588_RESET));

//	PORTD |= _BV(GPIO_WT588_RESET) | _BV(GPIO_WT588_DATA);
	PORTD |= _BV(GPIO_WT588_DATA);
}

void voice_play(int sound)
{
	while (voice_is_busy()) {
	}

	voice_send(sound);
}

static void voice_send(int command)
{
	uint8_t i;

	PORTD &= ~_BV(GPIO_WT588_DATA);
	_delay_ms(5);
	PORTD |= _BV(GPIO_WT588_DATA);

	for (i = 0; i < 8; i++) {
		if (command & 1) {
			PORTD |= _BV(GPIO_WT588_DATA);
			_delay_us(600);
			PORTD &= ~_BV(GPIO_WT588_DATA);
			_delay_us(200);
		} else {
			PORTD |= _BV(GPIO_WT588_DATA);
			_delay_us(200);
			PORTD &= ~_BV(GPIO_WT588_DATA);
			_delay_us(600);
		}

		command >>= 1;
	}

	PORTD |= _BV(GPIO_WT588_DATA);
	_delay_ms(20);
}

uint8_t voice_is_busy(void)
{
	if (PIND & _BV(GPIO_WT588_BUSY)) {
		return 0;
	} else {
		return 1;
	}
}
