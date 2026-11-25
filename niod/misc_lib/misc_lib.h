/******************************************************************************
 *
 *    misc_lib.h
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

#ifndef _MISC_LIB_H
#define _MISC_LIB_H

#ifndef PRIVATE
#define PRIVATE static
#endif

#ifndef PUBLIC
#define PUBLIC
#endif

#ifndef _BYTE_H
#define _BYTE_H

typedef char byte;
typedef char *byte_ptr;

#endif				// _BYTE_H

#ifndef _BOOL_H
#define _BOOL_H

typedef unsigned char bool;

#ifndef FALSE
#define FALSE  (0)
#endif

#ifndef TRUE
#define TRUE  !FALSE
#endif

#endif				// _BOOL_H

#ifndef _CHAR_PTR
#define _CHAR_PTR

typedef char *char_ptr;

#endif

#ifndef EOF
#define EOF       (-1)
#endif

/* ASCII Key Codes */

#ifndef NUL
#define NUL       (0)
#endif

#ifndef BS
#define BS        (8)
#endif

#ifndef LF
#define LF        (10)
#endif

#ifndef RET
#define RET       (10)
#endif

#ifndef ESC
#define ESC       (27)
#endif

#ifndef BUFSIZ
#define BUFSIZ    (8192)
#endif

#ifndef STDIN
#define STDIN     (0)
#endif

#ifndef STDOUT
#define STDOUT    (1)
#endif

#ifndef STDERR
#define STDERR    (2)
#endif

PUBLIC int uio_open_file_rd(const char *pathname);
PUBLIC int uio_open_file_wr(const char *pathname);
PUBLIC int uio_open_file_rw(const char *pathname);

PUBLIC int uio_write_byte(int fd, byte b);
PUBLIC byte uio_read_byte(int fd);

PUBLIC int uio_get_line(int fd, byte * line, int lim);
PUBLIC int uio_put_line(int fd, const byte * line);
PUBLIC int uio_put_linef(int fd, const char *format, ...);

PUBLIC int wlog_open_file(const char *pathname);
PUBLIC void wlog_open_fd(int fd_in);
PUBLIC int wlog(const char *format, ...);
PUBLIC int wlog_close(void);

#ifndef MAX_FILES
#define MAX_FILES 256
#endif

PUBLIC int get_home_dir(char *s);
PUBLIC bool file_exists(const char *s);
PUBLIC void check_dir(const char *s);
PUBLIC char *basename(char *s);

//
//  netstring concept from:
//
//    http://cr.yp.to/proto/netstrings.txt
//

#ifdef _STDIO_H
PUBLIC int encode_netstring(const char *buf, FILE * fp);
PUBLIC int decode_netstring(char *buf, FILE * fp);
#endif

PUBLIC int encode_netstring_fd(const char *buf, int fd);
PUBLIC int decode_netstring_fd(char *buf, int fd);

#ifndef MAX_LINE_LEN
#define MAX_LINE_LEN	 (81)
#endif

#define MAX_SERVICE_LEN  (6)
#define MAX_USERNAME_LEN (16)
#define MAX_SERVER_LEN   (80)
#define MAX_PORT_LEN     (8)
#define MAX_EXT_LEN      (5)

typedef struct {
	char service[MAX_SERVICE_LEN];
	char username[MAX_USERNAME_LEN];
	char server[MAX_LINE_LEN];
	char port[MAX_PORT_LEN];
	char program[MAX_LINE_LEN];
	char extension[MAX_EXT_LEN];
} url;

PUBLIC void parse_url(const char *s, url *);
PUBLIC void print_url(const url *);

#ifndef MAX
#define MAX(a,b) (a>b ? a : b)
#endif

//
//    From unix programming FAQ
// 
//    http://www.erlenstar.demon.co.uk/unix/faq_4.html
//

PUBLIC void echo_off(void);
PUBLIC void echo_on(void);

// From OpenBSD 

#ifndef _SYS_TYPES_H
#include <sys/types.h>
#endif

PUBLIC size_t strlcpy(char *dst, const char *src, size_t siz);
PUBLIC size_t strlcat(char *dst, const char *src, size_t siz);

// random

PUBLIC void randomize(void);

// path

#define PATH_SIZE  (256)

typedef char path[PATH_SIZE];

PUBLIC size_t pathcpy(path dst, const char_ptr src);
PUBLIC size_t pathcat(path dst, const char_ptr src);

#endif				// _MISC_LIB_H
