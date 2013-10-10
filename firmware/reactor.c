#include "common.h"
#include "effects.h"
#include "reactor.h"

void reactor_init()
{
	effect_init(GPIO_REACTOR);
}

void reactor_set_mode(uint8_t mode)
{
	effect_set_mode(GPIO_REACTOR, mode);
}
