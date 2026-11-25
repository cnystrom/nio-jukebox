/******************************************************************************
 *
 *    netstring.c
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

//
//  From:
//    http://cr.yp.to/proto/netstrings.txt
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "misc_lib.h"

PRIVATE int get_size(int fd);
PRIVATE int writef(int fd, const char *format, ...);

#ifndef BUFSIZ
#define BUFZIE  (8192)
#endif

int encode_netstring(const char *buf, FILE * fp)
{
	int len;

	len = strlen(buf);

	if (len <= 0 || len > BUFSIZ) {
		wlog("encode_netstring(): length bad.\n");
		return -1;
	}

	if (fprintf(fp, "%u:", len) < 0) {
		wlog("encode_netstring(): length bad.\n");
		return -2;
	}

	if (fwrite(buf, 1, len, fp) < len) {
		wlog("encode_netstring(): write failed.\n");
		return -3;
	}

	if (putc((','), fp) < 0) {
		wlog("encode_netstring(): missing comma.\n");
		return -4;
	}

	return (len);
}

int decode_netstring(char *buf, FILE * fp)
{
	int len;

	// >999999999 bytes is bad 
	if (fscanf(fp, "%9u", &len) < 1) {
		wlog("decode_netstring(): length bad.\n");
		return -1;
	}

	if (len <= 0 || len > BUFSIZ) {
		wlog("decode_netstring(): length bad.\n");
		return -2;
	}

	if (getc(fp) != ':') {
		wlog("decode_netstring(): missing colon.\n");
		return -3;
	}

	if (fread(buf, 1, len, fp) < len) {
		wlog("decode_netstring(): read failed.\n");
		return -4;
	}

	if (getc(fp) != ',') {
		wlog("decode_netstring(): missing comma.\n");
		return -5;
	}

	*(buf + len) = 0;

	return (len);
}

PUBLIC int encode_netstring_fd(const char *buf, int fd)
{
	int len;

	len = strlen(buf);

	if (len <= 0 || len > BUFSIZ) {
		fprintf(stderr, "encode_netstring(): length bad.\n");
		return -1;
	}

	if (writef(fd, "%u:", len) < 0) {
		fprintf(stderr, "encode_netstring(): length bad.\n");
		return -2;
	}

	if (write(fd, buf, len) < len) {
		fprintf(stderr, "encode_netstring(): write failed.\n");
		return -3;
	}

	if (write(fd, ",", 1) <= 0) {
		fprintf(stderr,
			"encode_netstring(): comma write failed.\n");
		return -4;
	}

	return (len);
}

PUBLIC int decode_netstring_fd(char *buf, int fd)
{
	char c;
	int len;

	len = get_size(fd);

	if (len <= 0 || len > BUFSIZ) {
		fprintf(stderr, "decode_netstring(): length bad.\n");
		return -2;
	}

	if (read(fd, buf, len) < len) {
		fprintf(stderr, "decode_netstring(): read failed.\n");
		return -4;
	}

	read(fd, &c, 1);

	if (c != ',') {
		fprintf(stderr, "decode_netstring(): missing comma.\n");
		return -5;
	}

	return (len);
}

PRIVATE int get_size(int fd)
{
	char c;
	int i = 0;
	char s[BUFSIZ];

	read(fd, &c, 1);

	while (c != NUL && c != ':') {
		s[i++] = c;
		read(fd, &c, 1);
	}

	s[i] = 0;

	return (atoi(s));
}

PRIVATE int writef(int fd, const char *format, ...)
{
	int len, ret;
	char buf[BUFSIZ];
	va_list ap;

	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);

	len = strlen(buf);

	ret = write(fd, buf, len);

	return (ret);
}

/*
int
main(void)
{
  char s[BUFSIZ];

  encode_netstring_fd("This is a test", STDOUT);

  printf("\nINPUT> ");
  fflush(stdout);

  // cut and paste above output into here to test
  decode_netstring_fd(s, STDIN);

  printf("\ns = |%s|\n", s);

  exit(0);
}
*/
