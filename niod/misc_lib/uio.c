/******************************************************************************
 *
 *    uio.c
 *
 *    unbuffered I/O functions
 *
 *    Copyright (C) 2004, 2005  Chris Nystrom
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
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "misc_lib.h"

PUBLIC int uio_open_file_rd(const char *pathname)
{
	int fd = open(pathname, O_RDONLY);

	return (fd);
}

PUBLIC int uio_open_file_wr(const char *pathname)
{
	int fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC,
		      S_IRUSR | S_IWUSR);

	return (fd);
}

PUBLIC int uio_open_file_rw(const char *pathname)
{
	int fd =
	    open(pathname, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	return (fd);
}

PUBLIC int uio_write_byte(int fd, byte b)
{
	int n = 0;

	while (n == 0) {
		n = write(fd, &b, 1);
	}

	// n < 0 -> error

	return (n);
}

PUBLIC byte uio_read_byte(int fd)
{
	byte b;
	int n;

	n = read(fd, &b, 1);

	if (n < 0) {		// Error condition
		return n;
	}

	if (n == 0) {		// nothing left to give
		return (EOF);
	}

	return b;
}

PUBLIC int uio_get_line(int fd, byte * line, int lim)
{
	byte b;
	int i = 0;

	while (i < (lim - 1)) {

		b = uio_read_byte(fd);

		if (b == EOF || b <= 0) {
			break;
		}

		if (b != 13) {	// char 13 not needed in unix
			*(line + i) = b;
			i++;
		}

		if (b == '\n') {
			break;
		}
	}

	*(line + i) = '\0';

	return i;
}

PUBLIC int uio_put_line(int fd, const byte * line)
{
	int i, len, ret = 0;

	len = strlen(line);

	for (i = 0; i < len; i++) {
		ret = uio_write_byte(fd, *(line + i));

		if (ret <= 0) {
			break;
		}
	}

	return (i);
}

PUBLIC int uio_put_linef(int fd, const char *format, ...)
{
	int ret;
	byte l[BUFSIZ];
	va_list ap;

	va_start(ap, format);
	vsprintf(l, format, ap);
	va_end(ap);

	ret = uio_put_line(fd, l);

	return (ret);
}

/*
int
main(void)
{
  byte l[BUFSIZ];

//  int log_fd = uio_open_file_wr("uio.log");

  while (1) {
    uio_get_line(STDIN, l, BUFSIZ);

    if (strncmp(l, "exit", 4) == 0) {
      break;
    }

    uio_put_line(STDOUT, l);
  }

//  close(log_fd);
}
*/
