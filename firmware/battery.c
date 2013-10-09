#define F_CPU 1000000UL

#include <avr/io.h>

#include "common.h"
#include "voice.h"
#include "battery.h"

uint16_t adc_offset = 0;

static uint8_t battery_measure_capacity(void);

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

void battery_get_capacity(void)
{
	uint8_t capacity = battery_measure_capacity();

	if (capacity == 0) {
		voice_play_sound(SOUND_JARVIS_BATTERY_LOW_1);
	} else {
		voice_play_sound(SOUND_JARVIS_BATTERY_POWER_AT);

		if (capacity <= 20) {
			voice_play_sound(SOUND_JARVIS_BATTERY_1 + (capacity - 1));
		} else {
			uint8_t remainder = capacity % 10;

			voice_play_sound(SOUND_JARVIS_BATTERY_20 + ((capacity / 10) - 2));

			if (remainder > 0) {
				voice_play_sound(SOUND_JARVIS_BATTERY_1 + (remainder - 1));
			}
		}
		voice_play_sound(SOUND_JARVIS_BATTERY_PERCENT);
	}
}

static uint8_t battery_measure_capacity(void)
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
