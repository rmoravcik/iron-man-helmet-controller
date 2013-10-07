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

void eyes_set_mode(uint8_t mode);

#endif // EYES_H
