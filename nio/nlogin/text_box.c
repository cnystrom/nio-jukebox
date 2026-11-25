/*
 *    text_box.c
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

#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "bool.h"
#include "ascii_key.h"
#include "colors.h"
#include "fonts.h"
#include "text.h"
#include "keyboard.h"
#include "screen.h"
#include "text_box.h"

char * get_mask_string(void);

static text_box_t tb;

static int tb_index;

static int x_home;
static int y_home;

static int font;
static int font_h;
static int font_w;

char mask_string[TB_MAX_COL + 1];

int
text_box(char *s, int num_char, int x, int y, int fn, Uint32 fg, Uint32 bg,
  bool pw)
{
  int c;
  SDL_Rect r;
  glyphFont gf;

//  printf("s = %s\n", s);

  tb_index = strlen(s);

  if (tb_index > num_char)
    fprintf(stderr, "text_box_init(): default entry larger than text box.\n");

  if (num_char <= TB_MAX_COL) {
    tb.len = num_char;
  }
  else {
    fprintf(stderr, "text_box_init(): text box size too large.\n");
    tb.len = TB_MAX_COL;
  }

  if (tb_index > 0) {
    strncpy(tb.str, s, tb_index);
  }
  else {
    strcpy(tb.str, "");
  }
  tb.str[tb_index] = '\0';

//  printf("tb.str = %s\n", tb.str);

  x_home = x;
  y_home = y;

  font = fn;

  gf = get_font(font);
  text_size(&gf, "X", &r);
  font_w = r.w; // font width
  font_h = gf.height;

//  printf("--\ntb.str = %s\n", tb.str);
//  printf("tb_index = %d\n", tb_index);

  draw_text_box(fg, bg, pw);

  for (;;) {
    c = get_char();

    if (c == ESC) {
      strncpy(s, tb.str, tb_index);
      s[tb_index] = '\0';
      return(ESC);
    } else if (c == BS) {
      if (tb_index > 0) {
        tb.str[--tb_index] = '\0';
      }
    }
    else if (c == RET) {
      strncpy(s, tb.str, tb_index);
      s[tb_index] = '\0';
      return(0);
    }
    else {
      if (tb_index <  num_char) {
        tb.str[tb_index++] = c;
        tb.str[tb_index] = '\0';
      }
    }

    draw_text_box(fg, bg, pw);

//    printf("--\ntb.str = %s\n", tb.str);
//    printf("tb_index = %d\n", tb_index);
  }

  return(-1); // Should not get here
}

void
draw_text_box(Uint32 fg, Uint32 bg, bool pw)
{
  Uint32 color;
  glyphFont gf;

  gf = get_font(font);
  draw_rectangle(x_home, y_home, (font_w - 1) * (tb.len + 2), font_h, fg);

  if (pw) {
    draw_text(&gf, get_mask_string(), x_home + font_w, y_home);
  }
  else {  
    draw_text(&gf, tb.str, x_home + font_w, y_home);
  }

  color = get_rand_color();
  text_box_show_cursor(color);
//  update_screen();
}

void
text_box_show_cursor(Uint32 bg)
{
  draw_rectangle(x_home + ((tb_index + 1) * (font_w - 1)) + 2,
    y_home, 2, 20, bg);
}

void
text_box_hide_cursor(Uint32 fg)
{
  draw_rectangle(x_home + ((tb_index + 1) * (font_w - 1)) + 2,
    y_home, 2, 22, fg);
}

char *
get_mask_string(void)
{
  int i, len;

  len = strlen(tb.str);

  for (i = 0; i < len; i++) {
    mask_string[i] = '*';
  }

  mask_string[len] = '\0';

  return(mask_string);
}

