/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * server.c
 * Copyright (C) 2017 Vladimir Roncevic <elektron.ronca@gmail.com>
 * 
 * rpiclient-gtk is free software: you can redistribute it and/or modify it
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

void server_run(struct in_addr local_address, uint16_t port) {
	struct sockaddr_in socket_address;
	int rval;
	struct sigaction sigchld_action;
	int server_socket;
	memset(&sigchld_action, 0, sizeof(sigchld_action));
	sigchld_action.sa_handler = &clean_up_child_process;
	sigaction(SIGCHLD, &sigchld_action, NULL);
	server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(server_socket == -1) {
		system_error(ERROR_CAUSE_SOCKET);
	}
	memset(&socket_address, 0, sizeof(socket_address));
	socket_address.sin_family = AF_INET;
	socket_address.sin_port = port;
	socket_address.sin_addr = local_address;
	rval = bind(
			server_socket,
			(const struct sockaddr *) &socket_address,
			sizeof(socket_address)
		);
	if(rval != 0) {
		system_error(ERROR_CAUSE_BIND);
	}
	rval = listen(server_socket, 10);
	if(rval != 0) {
		system_error(ERROR_CAUSE_LISTEN);
	}
	if(verbose == VERBOSE_ENABLE) {
		socklen_t address_length;
		address_length = sizeof(socket_address);
		rval = getsockname(
				server_socket,
				(struct sockaddr *) &socket_address,
				&address_length
			);
		if(rval == 0) {
			const char *msg = merge_str(
				MESSAGE_SERVER_LISTENING,
				inet_ntoa(socket_address.sin_addr)
			);
			verbose_message(
				merge_str(
					msg, itostr((int) ntohs(socket_address.sin_port))
				)
			);
		}
	}
	while(1) {
		struct sockaddr_in remote_address;
		socklen_t address_length;
		int connection;
		pid_t child_pid;
		address_length = sizeof(remote_address);
		connection = accept(
						server_socket,
						(struct sockaddr *) &remote_address,
						&address_length
					);
		if(connection == -1) {
			if(errno == EINTR) {
				continue;
			}
			else {
				system_error(ERROR_CAUSE_ACCEPT);
			}
		}
		if(verbose == VERBOSE_ENABLE) {
			socklen_t address_length;
			address_length = sizeof(socket_address);
			rval = getpeername(
						connection,
						(struct sockaddr *) &socket_address,
						&address_length
					);
			if(rval == 0) {
				verbose_message(
					merge_str(
						MESSAGE_CONNECTION_ACCEPTED,
						inet_ntoa(socket_address.sin_addr)
					)
				);
			}
		}
		child_pid = fork();
		if(child_pid == 0) {
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(server_socket);
			handle_connection(connection);
			close(connection);
			exit(0);
		} else if(child_pid > 0) {
			verbose_message(MESSAGE_CLOSE_CONNECTION);
			close(connection);
		} else {
			system_error(ERROR_CAUSE_FORK);
		}
	}
}

