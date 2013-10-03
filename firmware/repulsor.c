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
	voice_play(REPULSOR);
	_delay_ms(3000);

	PORTD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);
	_delay_ms(100);
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));

	if (!(PIND & _BV(GPIO_SHOT_REPULSOR))) {
		voice_play(REPULSOR);
	}

//	while (!(PIND & _BV(GPIO_SHOT_REPULSOR))) {
//		voice_play(REPULSOR);
//	}
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}
