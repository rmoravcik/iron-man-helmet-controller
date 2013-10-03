#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "helmet.h"
#include "voice.h"

static void pwm_enable(void)
{
	TCCR1A |= _BV(COM1A1) | _BV(COM1B1);
}

static void pwm_disable(void)
{
	TCCR1A &= ~(_BV(COM1A1) | _BV(COM1B1));
}

void helmet_init()
{
	ICR1 = 20000;

	TCCR1A = _BV(WGM11);
	TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

	DDRB |= _BV(GPIO_SERVO1) | _BV(GPIO_SERVO2) | _BV(GPIO_EYES);

	helmet_open();
}

void helmet_open(void)
{
	pwm_enable();

	OCR1A = 2200;
	OCR1B = 900;

	PORTB &= ~_BV(GPIO_EYES);

	_delay_ms(700);
	pwm_disable();

	_delay_ms(3000);
}

void helmet_close(void)
{
	pwm_enable();

	OCR1A = 900;
	OCR1B = 2200;

	_delay_ms(700);
	PORTB |= _BV(GPIO_EYES);

	pwm_disable();

	_delay_ms(3000);
}

uint8_t helmet_is_closed(void)
{
	if (PORTB & _BV(GPIO_EYES))
		return 1;
	else
		return 0;
}
