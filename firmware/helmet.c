#include <util/delay.h>

#include "common.h"
#include "helmet.h"

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

	DDRB |= _BV(GPIO_SERVO1) | _BV(GPIO_SERVO2);

	helmet_open();
}

void helmet_open(void)
{
	pwm_enable();

	OCR1A = 2200;
	OCR1B = 900;

	// wait till helmet is open
	_delay_ms(700);

	pwm_disable();
}

void helmet_close(void)
{
	pwm_enable();

	OCR1A = 900;
	OCR1B = 2200;

	// wait till helmet is closed
	_delay_ms(700);

	pwm_disable();
}

uint8_t helmet_state(void)
{
	if ((OCR1A == 900) && (OCR1B == 2200)) {
		return HELMET_CLOSED;
	} else {
		return HELMET_OPEN;
	}
}
