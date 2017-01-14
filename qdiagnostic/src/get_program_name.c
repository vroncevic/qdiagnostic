/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * get_program_name.c
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

char* get_program_name(pid_t pid) {
	char file_name[64];
	char status_info[256];
	int fd;
	int rval;
	char *open_paren;
	char *close_paren;
	char *result;
	snprintf(file_name, sizeof(file_name), QDIAGNOSTIC_STAT_PATH, (int) pid);
	fd = open(file_name, O_RDONLY);
	if(fd == -1) {
		return NULL;
	}
	rval = read(fd, status_info, sizeof(status_info) - 1);
	close(fd);
	if(rval <= 0) {
		return NULL;
	}
	status_info[rval] = '\0';
	open_paren = strchr(status_info, '(');
	close_paren = strchr(status_info, ')');
	if(open_paren == NULL || close_paren == NULL || close_paren < open_paren) {
		return NULL;
	}
	result = (char *) xmalloc(close_paren - open_paren);
	strncpy(result, open_paren + 1, close_paren - open_paren - 1);
	result[close_paren - open_paren - 1] = '\0';
	return result;
}

