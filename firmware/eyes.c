/*
 *  iron-man-helmet-controller
 *  Copyright (C) 2013 Roman Moravcik
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <util/delay.h>

#include "common.h"
#include "effects.h"
#include "eyes.h"

void eyes_init()
{
	effect_init(GPIO_EYES);
}

void eyes_power_up(void)
{
	effect_set_mode(GPIO_EYES, MODE_BLINK);
	effect_set_mode(GPIO_EYES, MODE_FADE_IN);
}

void eyes_power_down(void)
{
	effect_set_mode(GPIO_EYES, MODE_OFF);

	// wait for 200ms before opening helmet
	_delay_ms(200);
}

void eyes_power_failure(void)
{
	effect_set_mode(GPIO_EYES, MODE_BLINK);
}
