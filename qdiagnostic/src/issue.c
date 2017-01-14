/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * issue.c
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
#include <sys/sendfile.h>

static char *html_page_start = 
	"<html>\n"
	"	<body>\n"
	"		<pre>\n";

static char *html_page_end = 
	"		</pre>\n"
	"	</body>\n"
	"</html>\n";

static char *html_error_page = 
	"<html>\n"
	"	<body>\n"
	"		<p>Error: Could not open /proc/issue.</p>\n"
	"	</body>\n"
	"</html>\n";

static char *error_message = "Error reading /proc/issue.";

void module_generate(int fd) {
	int input_fd;
	struct stat file_info;
	int rval;
	verbose_message(MESSAGE_CALL_ISSUE_MODULE);
	input_fd = open(QDIAGNOSTIC_ISSUE_PATH, O_RDONLY);
	if(input_fd == -1) {
		system_error(ERROR_CAUSE_OPEN);
	}
	rval = fstat(input_fd, &file_info);
	if(rval == -1) {
		write(fd, html_error_page, strlen(html_error_page));
	} else {
		int rval;
		off_t offset = 0;
		write(fd, html_page_start, strlen(html_page_start));
		rval = sendfile(fd, input_fd, &offset, file_info.st_size);
		if(rval == -1) {
			write(fd, error_message, strlen(error_message));
		}
		write(fd, html_page_end, strlen(html_page_end));
	}
	close(input_fd);
}

