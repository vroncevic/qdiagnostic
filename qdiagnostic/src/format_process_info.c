/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * format_process_info.c
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

char* format_process_info(pid_t pid) {
	int rval;
	uid_t uid;
	gid_t gid;
	char *user_name;
	char *group_name;
	int rss;
	char *program_name;
	size_t result_length;
	char *result;
	rval = get_uid_gid(pid, &uid, &gid);
	if(rval != 0) {
		return NULL;
	}
	rss = get_rss(pid);
	if(rss == -1) {
		return NULL;
	}
	program_name = get_program_name(pid);
	if(program_name == NULL) {
		return NULL;
	}
	user_name = get_user_name(uid);
	group_name = get_group_name(gid);
	result_length = strlen(program_name) + 
						strlen(user_name) + 
							strlen(group_name) + 128;
	result = (char *) xmalloc(result_length);
	snprintf(
		result, result_length,
		"<tr><td align=\"right\">%d</td><td><tt>%s</tt></td><td>%s</td>"
		"<td>%s</td><td align=\"right\">%d</td></tr>\n",
		(int) pid, program_name, user_name, group_name, rss
	);
	free(program_name);
	free(user_name);
	free(group_name);
	return result;
}

