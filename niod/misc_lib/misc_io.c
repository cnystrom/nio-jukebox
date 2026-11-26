/******************************************************************************
 *
 *    misc_io.c
 *
 *    Copyright (C) 2002, 2005  Chris Nystrom
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU Lessor General Public License as published
 *    by the Free Software Foundation; either version 2.1 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but without any warranty whatsoever.
 *
 *    For more license information see:
 *
 *      http://www.gnu.org/copyleft/lessor.html
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "misc_lib.h"

#define PATH_SIZE  (256)

PUBLIC int get_home_dir(char *s)
{
	int len, i;
	char *tmp;

	if ((tmp = getenv("HOME")) == NULL) {
		fprintf(stderr, "get_home_dir(): HOME not found.\n");
		exit(1);
	}

	len = strlen(tmp);

//  printf("get_home_dir(): len = %d\n", len);

	i = strlcpy(s, tmp, PATH_SIZE);

//  printf("get_home_dir(): s = %s\n", s);
//  printf("get_home_dir(): i = %d\n", i);

	return (len);
}

PRIVATE bool dir_exists(const char *s)
{
	struct stat buf;

#ifdef UNIX
	if (lstat(s, &buf) < 0)
#else
	if (stat(s, &buf) < 0)
#endif
	{
		return (FALSE);
	}

	if (S_ISDIR(buf.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

PUBLIC bool file_exists(const char *s)
{
	struct stat buf;

#ifdef UNIX
	if (lstat(s, &buf) < 0)
#else
	if (stat(s, &buf) < 0)
#endif
	{
		return (FALSE);
	}

	if (S_ISREG(buf.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

PUBLIC void check_dir(const char *s)
{
	if (!dir_exists(s)) {
#ifdef UNIX
		if (mkdir(s, 0755) != 0)
#else
		if (mkdir(s) != 0)
#endif
		{
			fprintf(stderr,
				"check_dir(): mkdir failed for %s\n", s);
		}
	}
}

PUBLIC char *basename(char *s)
{
	char *s2 = s;

	while (*s) {
#ifdef UNIX
		if (*s++ == '/')
#else
		if (*s++ == '\\')
#endif
			s2 = s;
	}

	return (s2);
}
