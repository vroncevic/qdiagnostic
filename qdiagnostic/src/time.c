/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * time.c
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
#include <time.h>
#include <sys/time.h>

static char *html_time_page = 
	"<html>\n"
	"	<head>\n"
	"		<meta http-equiv=\"refresh\" content=\"5\">\n"
	"	</head>\n"
	"	<body>\n"
	"		<p>The current time is %s.</p>\n"
	"	</body>\n"
	"</html>\n";

void module_generate(int fd) {
	struct timeval tv;
	struct tm* tm_ptr;
	char time_string[40];
	FILE* fp;
	verbose_message(MESSAGE_CALL_TIME_MODULE);
	gettimeofday(&tv, NULL);
	tm_ptr = localtime(&tv.tv_sec);
	strftime(time_string, sizeof(time_string), "%H:%M:%S", tm_ptr);
	fp = fdopen(fd, "w");
	if(fp != NULL) {
		fprintf(fp, html_time_page, time_string);
		fflush(fp);
	}
}

