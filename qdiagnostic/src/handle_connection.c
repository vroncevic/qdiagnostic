/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * handle_connection.c
 * Copyright (C) 2017 Vladimir Roncevic <elektron.ronca@gmail.com>
 * 
 * rpiclient-gtk is free software: you can redistribute it and/or modify it
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
#include "server.h"

void handle_connection(int connection_fd) {
	char buffer[256];
	ssize_t bytes_read;
	bytes_read = read(connection_fd, buffer, sizeof(buffer) - 1);
	if(bytes_read > 0) {
		char method[sizeof (buffer)];
		char url[sizeof (buffer)];
		char protocol[sizeof (buffer)];
		buffer[bytes_read] = '\0';
		sscanf(buffer, "%s %s %s", method, url, protocol);
		while(strstr(buffer, "\r\n\r\n") == NULL) {
			bytes_read = read(connection_fd, buffer, sizeof(buffer));
		}
		if(bytes_read == -1) {
			close(connection_fd);
			return;
		}
		if(strcmp(protocol, "HTTP/1.0") && strcmp(protocol, "HTTP/1.1")) {
			write(
				connection_fd,
				HTML_BAD_REQ_RESPONSE,
				sizeof(HTML_BAD_REQ_RESPONSE)
			);
		} else if(strcmp(method, "GET")) {
			char response[1024];
			snprintf(
				response,
				sizeof(response),
				HTML_BAD_METHOD_RESPONSE,
				method
			);
			write(connection_fd, response, strlen(response));
		} else {
			handle_get(connection_fd, url);
		}
	} else if(bytes_read == 0) {
		;
	} else {
		system_error(ERROR_CAUSE_READ);
	}
}

