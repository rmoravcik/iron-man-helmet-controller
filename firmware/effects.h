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

#ifndef EFFECTS_H
#define EFFECTS_H

#include <stdint.h>

enum {
	MODE_OFF = 0,
	MODE_ON,
	MODE_BLINK,
	MODE_FADE_IN,
	MODE_FADE_OUT,
};

void effect_init(uint8_t gpio);

void effect_set_mode(uint8_t gpio, uint8_t mode);

#endif // EFFECTS_H
