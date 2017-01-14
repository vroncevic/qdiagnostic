/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * diskfree.c
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
#include <sys/types.h>
#include <sys/wait.h>

static char *html_page_start = 
	"<html>\n"
	"	<body>\n"
	"		<pre>\n";

static char *html_page_end = 
	"		</pre>\n"
	"	</body>\n"
	"</html>\n";

void module_generate(int fd) {
	pid_t child_pid;
	int rval;
	verbose_message(MESSAGE_CALL_DISKFREE_MODULE);
	write(fd, html_page_start, strlen(html_page_start));
	child_pid = fork();
	if(child_pid == 0) {
		char *argv[] = {QDIAGNOSTIC_DF_PATH, "-h", NULL};
		rval = dup2(fd, STDOUT_FILENO);
		if(rval == -1) {
			system_error(ERROR_CAUSE_DUP2);
		}
		rval = dup2(fd, STDERR_FILENO);
		if(rval == -1) {
			system_error(ERROR_CAUSE_DUP2);
		}
		execv(argv[0], argv);
		system_error(ERROR_CAUSE_EXECV);
	} else if(child_pid > 0) {
		rval = waitpid(child_pid, NULL, 0);
		if(rval == -1) {
			system_error(ERROR_CAUSE_WAITPID);
		}
	} else {
		system_error(ERROR_CAUSE_FORK);
	}
	write(fd, html_page_end, strlen(html_page_end));
}

