/******************************************************************************
 *
 *    wlog.c
 *
 *    write log: basic logging to file
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
#include <stdarg.h>
#include <unistd.h>
#include "misc_lib.h"

PRIVATE int fd;

PUBLIC int wlog_open_file(const char *pathname)
{
	fd = uio_open_file_wr(pathname);

	return (fd);
}

PUBLIC void wlog_open_fd(int fd_in)
{
	fd = fd_in;
}

PUBLIC int wlog(const char *format, ...)
{
	byte line[BUFSIZ];
	va_list ap;

	va_start(ap, format);
	vsnprintf((char *) line, sizeof(line), format, ap);
	va_end(ap);

	return (uio_put_line(fd, line));
}

PUBLIC int wlog_close(void)
{
	return (close(fd));
}
