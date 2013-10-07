#define F_CPU 1000000UL

#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "common.h"
#include "eyes.h"
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

	// Falling edge on INT0, falling edge on INT1
	MCUCR |= _BV(ISC11) | _BV(ISC01);

	// Enable INT0 and INT1 interrupts
	GIMSK |= _BV(INT1) | _BV(INT0);

	sei();
}

ISR(INT0_vect)
{
	uint8_t press_counter = 0;

	while (!(PIND & _BV(GPIO_OPEN_HELMET)) && press_counter < 10) {
		_delay_ms(200);
		press_counter++;
	}

	// short press of helmet button
	if (press_counter == 1) {
		if (helmet_state() == HELMET_CLOSED) {
			voice_play_sound(SOUND_JARVIS_BATTERY_FULL_2);
		} else {
			voice_play_sound(SOUND_JARVIS_EARLY_TO_RISE);
		}
	}

	// long press of helmet button
	if (press_counter == 10) {
		if (helmet_state() == HELMET_CLOSED) {
			// turn off eyes
			set_eyes(EYES_FADE_OUT);
			set_eyes(EYES_OFF);

			// open helmet
			helmet_open();
		} else {
			// close helmet
			helmet_close();

			// turn on eyes
			set_eyes(EYES_BLINK);
			set_eyes(EYES_FADE_IN);
			set_eyes(EYES_ON);

			// play welcome message
			voice_play_sound(SOUND_JARVIS_SCREEN_ON);
		}
	}

	sei();
}

ISR(INT1_vect)
{
	uint8_t press_counter = 0;

	while (!(PIND & _BV(GPIO_SHOT_REPULSOR)) && press_counter < 10) {
		_delay_ms(200);
		press_counter++;
	}

	// short press of repulsor button
	if (press_counter == 1) {
		if (helmet_state() == HELMET_CLOSED) {
			voice_play_sound(SOUND_JARVIS_BATTERY_FULL_3);
		} else {
			voice_play_sound(SOUND_JARVIS_ARC_REACTOR_MODE);
		}
	}

	// long press of repulsor button
	if (press_counter == 10) {
		if (helmet_state() == HELMET_CLOSED) {
			repulsor_shot();
		} else {
		}
	}

	sei();
}

int main(void)
{
	init();

	battery_init();
	eyes_init();
	repulsor_init();
	helmet_init();
	voice_init();

#ifdef VOICE_SILENT
	voice_set_volume(SOUND_VOLUME_2);
#endif

	battery_get_capacity();

	while(1) {
	}

	return 0;
}
