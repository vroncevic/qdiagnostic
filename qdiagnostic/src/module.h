/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * module.h
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
#ifndef __MODULE_H
#define __MODULE_H

#include "common.h"
#include <dlfcn.h>

#define MODULE_FUNCTION   "module_generate"

typedef struct {
	void *handle;
	const char *name;
	void (* generate_function) (int);
} ResponseModule;

ResponseModule* module_open(const char *module_path);
void module_close(ResponseModule *module);

#endif

