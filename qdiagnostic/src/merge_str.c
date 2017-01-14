/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * merge_str.c
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

char* merge_str(const char *s1, char *s2) {
	size_t s1_len = strlen(s1);
	size_t s2_len = strlen(s2);
	char *result;
	int i,j;
	result = malloc((s1_len + s2_len + 1) * (sizeof(char *)));
	strcpy(result,s1);
	for(i = s1_len,j = 0; ((i < (s1_len + s2_len)) && (j < s2_len)); i++,j++) {
		result[i] = s2[j];
	}
	result[s1_len + s2_len + 1] = '\0';
	return result;
}

