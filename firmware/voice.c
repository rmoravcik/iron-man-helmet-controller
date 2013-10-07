#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "voice.h"

static uint8_t voice_is_busy(void);
static void voice_send_command(uint8_t command);

void voice_init(void)
{
	// set DATA pin as an output
	DDRD |= _BV(GPIO_WT588_DATA);

	// set BUSY and RESET pins as an inputs
	DDRD &= ~(_BV(GPIO_WT588_BUSY) | _BV(GPIO_WT588_RESET));

	// set DATA pin to high
	PORTD |= _BV(GPIO_WT588_DATA);
}

void voice_play_sound(uint8_t sound)
{
	while (voice_is_busy()) {
	}

	voice_send_command(sound);
}

void voice_set_volume(uint8_t volume)
{
	voice_send_command(volume);
}

static uint8_t voice_is_busy(void)
{
	if (PIND & _BV(GPIO_WT588_BUSY)) {
		return 0;
	} else {
		return 1;
	}
}

static void voice_send_command(uint8_t command)
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

