#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"
#include "repulsor.h"

void repulsor_init(void)
{
	// set left/right repuslor pins as an output
	DDRD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);

	// set left/right repulsor pins to low
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}

void repulsor_shot(void)
{
	// simulate repulsor blast
	PORTD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);
	_delay_ms(200);
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}
