/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * get_self_executable_directory.c
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

char* get_self_executable_directory(void) {
	int rval;
	char link_target[1024];
	char *last_slash;
	size_t result_length;
	char *result;
	rval = readlink(QDIAGNOSTIC_EXE_PATH, link_target, sizeof(link_target));
	if(rval == -1) {
		return NULL;
	} else {
		link_target[rval] = '\0';
	}
	last_slash = strrchr(link_target, '/');
	if(last_slash == NULL || last_slash == link_target) {
		return NULL;
	}
	result_length = last_slash - link_target;
	result = (char *) xmalloc(result_length + 1);
	strncpy(result, link_target, result_length);
	result[result_length] = '\0';
	return result;
}

