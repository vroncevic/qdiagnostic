/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * usage.h
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
#ifndef __USAGE_H
#define __USAGE_H

#include "common.h"
#include <sys/stat.h>
#include <netdb.h>
#include <getopt.h>
#include <netinet/in.h>

#define USAGE_SHORT_OPTIONS   "a:hm:p:v"

#define USAGE_OPTIONS         "Usage: %s [ options ]\n" \
	"  -a, --address ADDR Bind to local address\n" \
	"  (by default, bindto all local addresses)\n" \
	"  -h, --help Print this information.\n" \
	"  -m, --module-dir DIR Load modules from specified directory\n" \
	"  (by default, use executable directory).\n" \
	"  -p, --port PORT Bind to specified port.\n" \
	"  -v, --verbose  Print verbose messages.\n"

void print_usage(int is_error);
void process_usage(
	int argc, char *const argv[],
	struct in_addr *local_address_ptr, uint16_t *port_ptr
);

#endif

