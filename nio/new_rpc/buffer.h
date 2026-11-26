/******************************************************************************
 *
 *    buffer.h
 *
 *    Copyright (C) 2005  <Chris Nystrom>
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
 *    E-Mail: cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _BUFFER_H
#define _BUFFER_H

#ifndef _TYPES_H
#include "types.h"
#endif // _TYPES_H

#ifndef BUF_SIZE
#define BUF_SIZE (8192)
#endif

void   display_buf(void);
void   reset_buf(void);

void   pack_int8(int8);
int8   unpack_int8(void);

void   pack_int16(int16);
int16  unpack_int16(void);

void   pack_int32(int32);
int32  unpack_int32(void);

void   pack_string(char *s);
void   unpack_string(char *s);

int    write_buffer(int fd);
int    read_buffer(int fd);
int    wr_buffer(int fd_out, int fd_in);

bool   cmp_buf(char *s);

#endif // _BUFFER_H

