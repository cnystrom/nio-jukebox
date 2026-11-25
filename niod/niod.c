/******************************************************************************
 *
 *    niod.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/gpl.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "misc_lib/misc_lib.h"

#define HOSTNAME_LEN  (256)
#define BIN_PATH  "/usr/local/nio/bin/"

int getline(char *line);
void strip_nl(char *s);
void print_string(const char *s);

int main(int argc, char *argv[])
{
	char hostname[HOSTNAME_LEN] = "appstest.newio.org";
	char s[BUFSIZ];
	path command;

	const char version[] = "0.10_bin_057";

	wlog_open_file("/var/tmp/niod.log");

//  gethostname(hostname, HOSTNAME_LEN);

	snprintf(s, BUFSIZ, "NIOd Test Server 0.10 (%s)", hostname);

	wlog("main(): welcome = |%s|\n", s);

	usleep(10000);

	printf(s);
	fflush(stdout);

	wlog("Welcome sent...\n");

	if (getline(s) > 0) {
		wlog("s = |%s|\n", s);
		strip_nl(s);
		wlog("s = |%s|\n", s);

		if (strncmp(s, version, 12)) {
			printf(version);
			fflush(stdout);
			wlog("Wrong browser version.\n");

			wlog("Exiting.\n");
			wlog_close();
			exit(0);
		} else {
			wlog("Correct browser version.\n");
			printf("0");
			fflush(stdout);
		}

		wlog("Getting command...\n");
		getline(s);

		wlog("s = |%s|\n", s);
		strip_nl(s);
		wlog("s = |%s|\n", s);

		pathcpy(command, BIN_PATH);
		pathcat(command, s);

		wlog("command = |%s|\n", command);

		if (file_exists(command)) {
			wlog("File |%s| exists.\n", command);
			printf("0");
			fflush(stdout);
			wlog("Return code sent.\n");

			wlog("Running |%s|...\n", command);
			system(command);
			wlog("back from system() call...\n");
		} else {
			wlog("File |%s| does not exist.\n", command);
			wlog("Sending return code: -1\n");
			printf("-1");
			fflush(stdout);
			wlog("Return code sent.\n");
		}
	}

	wlog("Exiting.\n");
	wlog_close();
	exit(0);
}

int getline(char *line)
{
	if (fgets(line, BUFSIZ, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

void strip_nl(char *s)
{
	int i, len;

//      wlog("s = |%s|\n", s);
//      print_string(s);

	len = strlen(s);

//      wlog("len = %d\n", len);

	for (i = 0; i < len; i++) {
		if (s[i] < 14) {
			s[i] = 0;
			break;
		}
	}

//      print_string(s);
//      wlog("s = |%s|\n", s);
}

/*
void print_string(const char *s)
{
	int i, len;

	len = strlen(s);

	for (i = 0; i < len; i++) {
		wlog("s[%d] = %d %c\n", i, s[i], s[i]);
	}
}
*/
