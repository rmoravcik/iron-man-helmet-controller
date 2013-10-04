#ifndef EYES_H
#define EYES_H

enum {
	EYES_OFF = 0,
	EYES_ON,
	EYES_BLINK,
	EYES_FADE_IN,
	EYES_FADE_OUT,
};

void eyes_init(void);

void set_eyes(uint8_t cmd);

#endif // EYES_H
