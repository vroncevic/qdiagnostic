##
## @info   gencpro ver.1.0
## @author Vladimir Roncevic <elektron.ronca@gmail.com>
## @brief  Process this file with automake to produce Makefile.in
##

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS = \
	-Wall \
	-g

bin_PROGRAMS = qdiagnostic $(qdiagnostic_MODULES)

qdiagnostic_MODULES = \
	diskfree.so \
	issue.so \
	processes.so \
	time.so

qdiagnostic_SOURCES = \
	paths.h \
	messages.h \
	errors.h \
	common.h \
	usage.h \
	server.h \
	module.h \
	number_places.c \
	itostr.c \
	merge_str.c \
	verbose_message.c \
	error.c \
	system_error.c \
	clean_up_child_process.c \
	get_program_name.c \
	handle_connection.c \
	xmalloc.c \
	get_rss.c \
	handle_get.c \
	xrealloc.c \
	get_self_executable_directory.c \
	xstrdup.c \
	format_process_info.c \
	get_uid_gid.c \
	get_group_name.c \
	get_user_name.c \
	print_usage.c \
	process_usage.c \
	module.c \
	server.c \
	main.c

$(qdiagnostic_MODULES): %.so:%.c common.h server.h
	$(AM_V_CC)$(COMPILE) $(AM_CFLAGS) -fPIC -shared -o $@ $<

qdiagnostic_LDFLAGS = -Wl,-export-dynamic

qdiagnostic_LDADD = -ldl

