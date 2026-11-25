/*
 *    term.h
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

#ifndef _NIO_TERM_H
#define _NIO_TERM_H

#ifndef MAX
#define MAX(a,b) (a>b ? a : b)
#endif

#define MAXROW  (128)
#define MAXCOL  (512)

/* Standard Terminal Sizes */

#define DEFAULT_FG_COLOR  "white"
#define DEFAULT_BG_COLOR  "black"

struct term_char_struct
{
//  int fg_color;
//  int bg_color;
  int c;
};

typedef struct term_char_struct term_char;

struct term_line_struct
{
  term_char tc[MAXCOL];
  int len;
};

typedef struct term_line_struct term_line;

typedef term_line term_screen[MAXROW];

//typedef char screen[MAXROW][MAXCOL];

void term_init(int fn, Uint32 bg_color);
void term_scroll(void);
void term_debug(void);
void increment_row(void);
void term_clear(void);
void term_draw(void);
void term_put_char(int c);
void term_draw_char(int row, int col);
//void term_set_fg_color(char *color);
//void term_set_bg_color(char *color);
void term_reverse_video(void);
void term_print(char *s);
void term_show_cursor(void);
void term_clear_cursor(void);

#endif /* _NIO_TERM_H */

