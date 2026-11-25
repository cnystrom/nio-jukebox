/*
 *    sock_lib.h
 *
 *    Copyright (C) 2002  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: ccn@olenska.hn.org or nystrom@cactus.org
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _SOCK_LIB_H
#define _SOCK_LIB_H

#ifdef WIN32
#include <winsock.h>
#else
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <unistd.h>
#endif

#ifndef _TYPES_H
#include "types.h"
#endif

#ifndef SOCKET
#define SOCKET int
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifdef  __cplusplus
extern "C" {
#endif

SOCKET establish_socket(Uint16 portnum);
SOCKET open_socket(Uint16 portnum);
SOCKET accept_socket(SOCKET s);
void   close_socket(SOCKET s);

void  puts_socket(SOCKET s, char *str);
u_int gets_socket(SOCKET s, char *str, u_int max_len);

SOCKET call_socket(const char *hostname, unsigned short portnum);

int read_socket(SOCKET s, byte *buf, int n);
int write_socket(SOCKET s, byte *buf, int n);

#ifdef  __cplusplus
}
#endif

#endif /* _SOCK_LIB_H */

