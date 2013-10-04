#ifndef EYES_H
#define EYES_H

enum {
	EYES_OFF = 0,
	EYES_ON
};

void eyes_init(void);

void set_eyes(uint8_t cmd);
uint8_t get_eyes(void);

#endif // EYES_H
