/*
 *    text_box.h
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
 *    Soli Deo Gloria
 *
 */

#ifndef _NIO_TEXT_BOX_H
#define _NIO_TEXT_BOX_H

#define TB_MAX_COL  (80)

typedef struct
{
  int x;
  int y;
  char str[TB_MAX_COL + 1];
  int len;
} text_box_t;

int text_box(char *s, int num_char, int x, int y, int fn, Uint32 fg, Uint32 bg,   bool pw);
void draw_text_box(Uint32 fg, Uint32 bg, bool pw);
void text_box_show_cursor(Uint32 bg);
void text_box_hide_cursor(Uint32 fg);

#endif /* _NIO_TEXT_BOX_H */

