#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "repulsor.h"
#include "voice.h"

void repulsor_init(void)
{
	DDRD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);
	DDRD &= ~_BV(GPIO_SHOT_REPULSOR);
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}

void repulsor_shot(void)
{
	voice_play_sound(SOUND_REPULSOR);
	_delay_ms(1000);

	PORTD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);
	_delay_ms(200);
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}
