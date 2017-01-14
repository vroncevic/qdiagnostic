/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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
#include "usage.h"

char *module_dir;
int verbose = VERBOSE_ENABLE;

int main(int argc, char* const argv[]) {
	struct in_addr local_address;
	uint16_t port;
	verbose_message(MESSAGE_GET_EXE_DIR);
	module_dir = get_self_executable_directory();
	if(module_dir != NULL) {
		process_usage(argc, argv, &local_address, &port);
		verbose_message(merge_str(MESSAGE_GET_MODULE_DIR, module_dir));
		server_run(local_address, port);
	}
	return 0;
}

