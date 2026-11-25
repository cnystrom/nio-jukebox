/******************************************************************************
 *
 *    types.h
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
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#ifndef _TYPES_H
#define _TYPES_H

typedef char            int8;
typedef short           int16;
typedef int             int32;

#ifndef _SDL_H

typedef unsigned char   Uint8;
typedef signed char     Sint8;
typedef unsigned short  Uint16;
typedef signed short    Sint16;
typedef unsigned int    Uint32;
typedef signed int      Sint32;

#endif // _SDL_H

typedef char            byte;

// Size in bytes of types
#define BYTE_SIZE   (1)  // Haha
#define INT8_SIZE   (1)
#define INT16_SIZE  (2)
#define INT32_SIZE  (4)
#define FLT_SIZE    (4)
#define DBL_SIZE    (8)
#define WCHAR_SIZE  (4)  // For unicode chars

#ifndef _BOOL_H

typedef unsigned char   bool;

#ifndef FALSE
#define FALSE  (0)
#endif

#ifndef TRUE
#define TRUE  !FALSE
#endif

#endif // _BOOL_H

#endif // _TYPES_H

