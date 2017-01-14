/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * server.c
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
#ifndef __SERVER_H
#define __SERVER_H

#include "common.h"
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define HTML_OK_RESPONSE           "HTTP/1.0 200 OK\n" \
								   "Content-type: text/html\n" \
								   "\n"

#define HTML_BAD_REQ_MSG		   "This server did not understand request."

#define HTML_BAD_REQ_RESPONSE      "HTTP/1.0 400 Bad Request\n" \
								   "Content-type: text/html\n" \
								   "\n" \
								   "<html>\n" \
								   "<body>\n" \
								   "<h1>Bad Request</h1>\n" \
								   "<p>%s</p>\n" \
								   "</body>\n" \
								   "</html>\n"

#define HTML_NOT_FOUND_MSG         

#define HTML_NOT_FOUND_RESPONSE    "HTTP/1.0 404 Not Found\n" \
								   "Content-type: text/html\n" \
								   "\n" \
								   "<html>\n" \
								   "<body>\n" \
								   "<h1>Not Found</h1>\n" \
								   "<p>Requested URL %s was not found.</p>\n" \
								   "</body>\n" \
								   "</html>\n"

#define HTML_BAD_METHOD_RESPONSE   "HTTP/1.0 501 Method Not Implemented\n" \
								   "Content-type: text/html\n" \
								   "\n" \
								   "<html>\n" \
								   "<body>\n" \
								   "<h1>Method Not Implemented</h1>\n" \
								   "<p>Method %s is not implemented.</p>\n" \
								   "</body>\n" \
								   "</html>\n"

void clean_up_child_process(int signal_number);
void handle_get(int connection_fd, const char* page);
void handle_connection(int connection_fd);
void server_run(struct in_addr local_address, uint16_t port);

extern char* module_dir;
extern int verbose;

#endif

