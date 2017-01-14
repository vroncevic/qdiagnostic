/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * handle_get.c
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
#include "server.h"
#include "module.h"

void handle_get(int connection_fd, const char *page) {
	ResponseModule *module = NULL;
	if(*page == '/' && strchr(page + 1, '/') == NULL) {
		char module_file_name[64];
		snprintf(module_file_name, sizeof(module_file_name), "%s.so", page + 1);
		module = module_open(module_file_name);
	}
	if(module == NULL) {
		char response[1024];
		snprintf(response, sizeof(response), HTML_NOT_FOUND_RESPONSE, page);
		write(connection_fd, response, strlen(response));
	} else {
		write(connection_fd, HTML_OK_RESPONSE, strlen(HTML_OK_RESPONSE));
		(*module->generate_function) (connection_fd);
		module_close(module);
	}
}

