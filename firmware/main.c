#define F_CPU 1000000UL

#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "common.h"
#include "helmet.h"
#include "repulsor.h"
#include "voice.h"

static void init(void)
{
	DDRB = 0xff;
	DDRC = 0xff;

	DDRD = 0xff;
	DDRD &= ~(_BV(GPIO_OPEN_HELMET) | _BV(GPIO_SHOT_REPULSOR));
	PORTD |= _BV(GPIO_OPEN_HELMET) | _BV(GPIO_SHOT_REPULSOR);

	MCUCR |= _BV(ISC11) | _BV(ISC01) | _BV(ISC00);
	GIMSK |= _BV(INT1) | _BV(INT0);

	sei();
}

ISR(INT0_vect)
{
	if (helmet_is_closed()) {
		helmet_open();
	} else {
		helmet_close();
	}
}

ISR(INT1_vect)
{
    repulsor_shot();
}

int main(void)
{
	init();

	eyes_init();
	repulsor_init();
	helmet_init();
	voice_init();

	while(1) {
	}

	return 0;
}
