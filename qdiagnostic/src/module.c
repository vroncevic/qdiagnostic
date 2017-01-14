/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * module.c
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
#include "module.h"

ResponseModule* module_open(const char *module_name) {
	char *module_path;
	void *handle;
	void (* module_generate) (int);
	ResponseModule* module;
	module_path = (char *) xmalloc(
							strlen(get_self_executable_directory()) +
							strlen(module_name) + 2
				);
	sprintf(module_path, "%s/%s", get_self_executable_directory(), module_name);
	handle = dlopen(module_path, RTLD_NOW);
	if(handle == NULL) {
		return NULL;
	}
	module_generate = (void (*) (int)) dlsym(handle, MODULE_FUNCTION);
	if(module_generate == NULL) {
		dlclose(handle);
		return NULL;
	}
	module = (ResponseModule *) xmalloc(sizeof(ResponseModule));
	module->handle = handle;
	module->name = xstrdup(module_name);
	module->generate_function = module_generate;
	return module;
}

void module_close(ResponseModule *module) {
	dlclose(module->handle);
	free((char*) module->name);
	free(module);
}

