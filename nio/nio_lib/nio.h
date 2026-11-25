/*
 *    nio.h
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
 *    E-Mail: ccn@olenska.hn.org, nystrom@cactus.org,
 *              or cnystrom@talmid.sps.mot.com
 *
 *    Soli Deo Gloria
 *
 */

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _NIO_H
#define _NIO_H

#define VERSION                  (1)

// NIO Function Numbers

#define NIO_INIT                 (1)
#define NIO_EXIT                 (2)
#define NIO_CHAR_TO_STDOUT       (3)
#define NIO_STRING_TO_STDOUT     (4)
#define NIO_INT_TO_STDOUT        (5)
#define	NIO_GET_CHAR             (6)
#define NIO_PUT_CHAR             (7)
#define NIO_MOUSE_STATE          (8)
#define NIO_SYSTEM_LOCAL         (9)
#define NIO_GET_COLOR           (10)
#define NIO_GET_COLOR_RGB       (11)
#define NIO_GET_RAND_COLOR      (12)
#define NIO_LOAD_FONT           (13)
#define NIO_LOAD_SYS_FONT       (14)
#define NIO_FREE_FONT           (15)
#define NIO_DRAW_TEXT           (16)
#define NIO_SET_SCREEN          (17)
#define NIO_CLEAR_SCREEN        (18)
#define NIO_DRAW_RECTANGLE      (19)
#define NIO_DRAW_RECTANGLE_RGB  (20)
#define NIO_DRAW_RECTANGLE_RAND (21)
#define NIO_DRAW_POINT          (22)
#define NIO_DRAW_POINT_RGB      (23)
#define NIO_DRAW_POINT_RAND     (24)
#define NIO_DRAW_LINE           (25)
#define NIO_DRAW_LINE_RGB       (26)
#define NIO_DRAW_LINE_RAND      (27)
#define NIO_DRAW_ARC            (28)
#define NIO_DRAW_ARC_RGB        (29)
#define NIO_DRAW_ARC_RAND       (30)
#define NIO_SOUND               (31)
#define NIO_BEEP                (32)
#define NIO_LOAD_MUSIC          (33)
#define NIO_PLAY_MUSIC          (34)
#define NIO_STOP_MUSIC          (35)
#define NIO_MUSIC_PLAYING       (36)
#define NIO_LOAD_SOUND          (37)
#define NIO_PLAY_SOUND          (38)
#define NIO_FREE_SOUND          (39)
#define NIO_LOAD_IMAGE          (40)
#define NIO_DRAW_IMAGE          (41)
#define NIO_FREE_IMAGE          (42)
#define NIO_TERM_INIT           (43)
#define NIO_PRINT               (44)

#endif // _NIO_H

#ifdef  __cplusplus
}
#endif

