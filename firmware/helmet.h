#ifndef HELMET_H
#define HELMET_H

enum {
	SERVO1 = 0,
	SERVO2
};

void helmet_init(void);

void helmet_open(void);
void helmet_close(void);
uint8_t helmet_is_closed(void);

#endif // HELMET_H
