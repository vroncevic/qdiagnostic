/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * itostr.c
 * Copyright (C) 2017 Vladimir Roncevic <elektron.ronca@gmail.com>
 * 
 * qdiagnostic is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qdiagnostic is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "common.h"

char* itostr(int i) {
	char const digit[] = "0123456789";
	char *string_num = (char *) xmalloc(number_places(i));
	if(i < 0) {
		*string_num++ = '-';
		i *= -1;
	}
	int shifter = i;
	do {
		++string_num;
		shifter = shifter / 10;
	} while(shifter);
	*string_num = '\0';
	do {
		*--string_num = digit[i % 10];
		i = i/10;
	} while(i);
	return string_num;
}

