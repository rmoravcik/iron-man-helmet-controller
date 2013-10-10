#include "common.h"
#include "battery.h"

uint16_t adc_offset = 0;

void battery_init(void)
{
	// set battery sense pin as an input
	DDRC &= ~_BV(GPIO_BATTERY_SENSE);

	// enable internal 2.56V reference
	ADMUX |= _BV(REFS1) | _BV(REFS0);

	// enable ADC, set prescaler to 64
	ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);

	// set MUX channel to GND to measure offset
	ADMUX |= _BV(MUX3) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);

	// measure ADC offset
	ADCSRA |= _BV(ADSC);

	// wait will ADC complete
	while (ADCSRA & _BV(ADSC)) {
	}

	adc_offset = ADCW;

	// set MUX channel to ADC5 (battery sense pin)
	ADMUX |= _BV(MUX2) | _BV(MUX0);
	ADMUX &= ~(_BV(MUX3) | _BV(MUX1));
}

uint8_t battery_get_capacity(void)
{
	uint8_t capacity = 0;

	// start ADC conversion
	ADCSRA |= _BV(ADSC);

	// wait will ADC complete
	while (ADCSRA & _BV(ADSC)) {
	}

	// calc capacity of battery
	capacity = (ADCW - 800 - adc_offset) / 2;

	// return maximum capacity 100%
	if (capacity > 100)
		capacity = 100;

	return capacity;
}
