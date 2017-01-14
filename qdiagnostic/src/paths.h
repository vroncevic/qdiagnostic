/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * paths.h
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
#ifndef __PATHS_H
#define __PATHS_H

#define QDIAGNOSTIC_DF_PATH      "/bin/df"
#define QDIAGNOSTIC_STAT_PATH    "/proc/%d/stat"
#define QDIAGNOSTIC_STATM_PATH   "/proc/%d/statm"
#define QDIAGNOSTIC_EXE_PATH     "/proc/self/exe"
#define QDIAGNOSTIC_PID_PATH     "/proc/%d"
#define QDIAGNOSTIC_ISSUE_PATH   "/etc/issue"
#define QDIAGNOSTIC_PROC_PATH    "/proc"

#endif

