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
#include "repulsor.h"

void repulsor_init(void)
{
	effect_init(GPIO_REPULSOR_PWR);

	// set left/right repuslor pins as an output
	DDRD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);

	// set left/right repulsor pins to low
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}

void repulsor_shot(void)
{
	// simulate repulsor blast
	PORTD |= _BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR);
	_delay_ms(200);
	PORTD &= ~(_BV(GPIO_LEFT_REPULSOR) | _BV(GPIO_RIGHT_REPULSOR));
}

void repulsor_set_mode(uint8_t mode)
{
	effect_set_mode(GPIO_REPULSOR_PWR, mode);
}