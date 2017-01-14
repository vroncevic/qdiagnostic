/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * get_uid_gid.c
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
#include <sys/stat.h>

int get_uid_gid(pid_t pid, uid_t* uid, gid_t* gid) {
	char dir_name[64];
	struct stat dir_info;
	int rval;
	snprintf(dir_name, sizeof(dir_name), QDIAGNOSTIC_PID_PATH, (int) pid);
	rval = stat(dir_name, &dir_info);
	if(rval != 0) {
		return 1;
	}
/*	if(S_ISDIR(dir_info.st_mode)) {*/
		*uid = dir_info.st_uid;
		*gid = dir_info.st_gid;
/*	}*/
	return 0;
}

