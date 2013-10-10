#ifndef BATTERY_H
#define BATTERY_H

#include <stdint.h>

void battery_init(void);

uint8_t battery_get_capacity(void);

#endif // BATTERY_H
