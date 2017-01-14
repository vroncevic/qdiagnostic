/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * common.h
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
#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "paths.h"
#include "messages.h"
#include "errors.h"

#define APPLICATION_NAME   "qdiagnostic"

void* xmalloc(size_t size);
void* xrealloc(void *ptr, size_t size);
char* xstrdup(const char *s);
void system_error(const char *operation);
void error(const char *cause, const char *message);
char* get_self_executable_directory(void);
char* merge_str(const char *s1, char *s2);
void verbose_message(const char *message);
int number_places(int i);
char* itostr(int i);
int get_uid_gid(pid_t pid, uid_t *uid, gid_t *gid);
char* get_user_name(uid_t uid);
char* get_group_name(gid_t gid);
char* get_program_name(pid_t pid);
int get_rss(pid_t pid);
char* format_process_info(pid_t pid);

#endif

