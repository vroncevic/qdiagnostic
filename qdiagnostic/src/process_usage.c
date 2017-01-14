/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * process_usage.c
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

void process_usage(
	int argc, char *const argv[],
	struct in_addr *local_address_ptr, uint16_t *port_ptr) {
	int next_option;
	const struct option long_options[] = {
		{"address", 1, NULL, 'a'},
		{"help", 0, NULL, 'h'},
		{"module-dir", 1, NULL, 'm'},
		{"port", 1, NULL, 'p'},
		{"verbose", 0, NULL, 'v'},
	};
	local_address_ptr->s_addr = INADDR_ANY;
	*port_ptr = 0;
	do {
		next_option = getopt_long(
						argc, argv, USAGE_SHORT_OPTIONS, long_options, NULL
					);
		switch(next_option) {
			case 'a':
					{
						struct hostent *host_name;
						host_name = gethostbyname(optarg);
						if(host_name == NULL || host_name->h_length == 0) {
							error(optarg, ERROR_INVALID_NAME);
						} else {
							local_address_ptr->s_addr = 
								*((int*) (host_name->h_addr_list[0]));
						}
					}
					break;
			case 'h':
					print_usage(0);
			case 'm':
					{
						struct stat dir_info;
						if(access(optarg, F_OK) != 0) {
							error(optarg, ERROR_MODULE_DIR);
						}
						if(access (optarg, R_OK | X_OK) != 0) {
							error(optarg, ERROR_MODULE_DIR_NOT_ACCESSIBLE);
						}
						if(stat(optarg, &dir_info) != 0 || !S_ISDIR(dir_info.st_mode)) {
							error(optarg, ERROR_NOT_DIR);
						}
						module_dir = strdup(optarg);
					}
					break;
			case 'p':
					{
						long value;
						char *end;
						value = strtol(optarg, &end, 10);
						if(*end != '\0') {
							print_usage(1);
						}
						*port_ptr = (uint16_t) htons(value);
					}
					break;
			case 'v':
					verbose = VERBOSE_ENABLE;
					break;
			case '?':
					print_usage(1);
			case -1:
					break;
			default:
					abort();
		}
	} while(next_option != -1);
	if(optind != argc) {
		print_usage(1);
	}
}

