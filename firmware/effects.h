#ifndef EFFECTS_H
#define EFFECTS_H

#include <stdint.h>

enum {
	MODE_OFF = 0,
	MODE_ON,
	MODE_BLINK,
	MODE_FADE_IN,
	MODE_FADE_OUT,
};

void effect_init(uint8_t gpio);

void effect_set_mode(uint8_t gpio, uint8_t mode);

#endif // EFFECTS_H
