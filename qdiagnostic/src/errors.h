/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * errors.h
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
#ifndef __ERRORS_H
#define __ERRORS_H

#define ERROR_CAUSE_DUP2                  "dup2"
#define ERROR_CAUSE_EXECV                 "execv"
#define ERROR_CAUSE_WAITPID               "waitpid"
#define ERROR_CAUSE_FORK                  "fork"
#define ERROR_CAUSE_GETGRGID              "getgrgid"
#define ERROR_CAUSE_GETPWUID              "getpwuid"
#define ERROR_CAUSE_READ                  "read"
#define ERROR_CAUSE_OPEN                  "open"
#define ERROR_CAUSE_OPENDIR               "opendir"
#define ERROR_CAUSE_SOCKET                "socket"
#define ERROR_CAUSE_BIND                  "bind"
#define ERROR_CAUSE_LISTEN                "listen"
#define ERROR_CAUSE_ACCEPT                "accept"
#define ERROR_NOT_DIR                     "not a directory"
#define ERROR_INVALID_NAME                "invalid host name"
#define ERROR_MODULE_DIR                  "module directory does not exist"
#define ERROR_MODULE_DIR_NOT_ACCESSIBLE   "module directory is not accessible"

#endif

