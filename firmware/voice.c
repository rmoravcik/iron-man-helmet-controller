#include <util/delay.h>

#include "common.h"
#include "voice.h"

static void voice_send_command(uint8_t command);

void voice_init(void)
{
	// set DATA pin as an output
	DDRD |= _BV(GPIO_WT588_DATA);

	// set BUSY and RESET pins as an inputs
	DDRB &= ~_BV(GPIO_WT588_BUSY);
	DDRD &= ~_BV(GPIO_WT588_RESET);

	// set DATA pin to high
	PORTD |= _BV(GPIO_WT588_DATA);

	_delay_ms(100);
}

void voice_play_sound(uint8_t sound)
{
	// send command to play a sound
	voice_send_command(sound);

	// wait till busy signal is asserted low by voice module
	while (PINB & _BV(GPIO_WT588_BUSY)) {
	}

	// busy signal is held down for 32ms
	_delay_ms(40);
}

void voice_play_sound_no_wait(uint8_t sound)
{
	// send command to play a sound
	voice_send_command(sound);
}

void voice_set_volume(uint8_t volume)
{
	voice_send_command(volume);
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

