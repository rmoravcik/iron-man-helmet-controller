#include "common.h"
#include "effects.h"
#include "eyes.h"

void eyes_init()
{
	effect_init(GPIO_EYES);
}

void eyes_set_mode(uint8_t mode)
{
	effect_set_mode(GPIO_EYES, mode);
}
