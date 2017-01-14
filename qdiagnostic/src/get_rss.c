/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * get_rss.c
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

int get_rss(pid_t pid) {
	char file_name[64];
	int fd;
	char mem_info[128];
	int rval;
	int rss;
	snprintf(file_name, sizeof(file_name), QDIAGNOSTIC_STATM_PATH, (int) pid);
	fd = open(file_name, O_RDONLY);
	if(fd == -1) {
		return (-1);
	}
	rval = read(fd, mem_info, sizeof(mem_info) - 1);
	close(fd);
	if(rval <= 0) {
		return (-1);
	}
	mem_info[rval] = '\0';
	rval = sscanf(mem_info, "%*d %d", &rss);
	if(rval != 1) {
		return (-1);
	}
	return (rss * getpagesize() / 1024);
}

