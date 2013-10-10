#ifndef HELMET_H
#define HELMET_H

#include <stdint.h>

enum {
	HELMET_CLOSED = 0,
	HELMET_OPEN
};

void helmet_init(void);

void helmet_open(void);
void helmet_close(void);

uint8_t helmet_state(void);

#endif // HELMET_H
