/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * processes.c
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
#include <dirent.h>
#include <sys/uio.h>

static char *html_page_start = 
	"<html>\n"
	"	<body>\n"
	"		<table cellpadding=\"4\" cellspacing=\"0\" border=\"1\">\n"
	"			<thead>\n"
	"				<tr>\n"
	"					<th>PID</th>\n"
	"					<th>Program</th>\n"
	"					<th>User</th>\n"
	"					<th>Group</th>\n"
	"					<th>RSS&nbsp;(KB)</th>\n"
	"				</tr>\n"
	"			</thead>\n"
	"			<tbody>\n";

static char *html_table_error = 
	"				<tr><td colspan=\"5\">ERROR</td></tr>";

static char *html_page_end = 
	"			</tbody>\n"
	"		</table>\n"
	"	</body>\n"
	"</html>\n";

void module_generate(int fd) {
	size_t i;
	DIR *proc_listing;
	size_t vec_length = 0;
	size_t v_size = 16;
	verbose_message(MESSAGE_CALL_PROCESSES_MODULE);
	struct iovec *vec = 
		(struct iovec*) xmalloc(v_size * (sizeof(struct iovec)));
	vec[vec_length].iov_base = html_page_start;
	vec[vec_length].iov_len = strlen(html_page_start);
	++vec_length;
	proc_listing = opendir(QDIAGNOSTIC_PROC_PATH);
	if(proc_listing == NULL) {
		system_error(ERROR_CAUSE_OPENDIR);
	}
	while(1) {
		struct dirent *proc_entry;
		const char *name;
		pid_t pid;
		char *process_info;
		proc_entry  = readdir(proc_listing);
		if(proc_entry == NULL) {
			break;
		}
		name = proc_entry->d_name;
		if(strspn(name, "0123456789") != strlen(name)) {
			continue;
		}
		pid = (pid_t) atoi(name);
		process_info = format_process_info(pid);
		if(process_info == NULL) {
			process_info = html_table_error;
		}
		if(vec_length == v_size - 1) {
			v_size *= 2;
			vec = xrealloc(vec, v_size * (sizeof(struct iovec)));
		}
		vec[vec_length].iov_base = process_info;
		vec[vec_length].iov_len = strlen(process_info);
		++vec_length;
	}
	closedir(proc_listing);
	vec[vec_length].iov_base = html_page_end;
	vec[vec_length].iov_len = strlen(html_page_end);
	++vec_length;
	writev(fd, vec, vec_length);
	for(i = 1; i < vec_length - 1; ++i) {
		free(vec[i].iov_base);
	}
	free(vec);
}

