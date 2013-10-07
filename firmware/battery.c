#define F_CPU 1000000UL

#include <avr/io.h>

#include "common.h"
#include "voice.h"
#include "battery.h"

void battery_init(void)
{
}

void battery_get_capacity(void)
{
	uint8_t capacity = 81;

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
