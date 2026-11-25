/*
 *    term.c
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

#include <string.h>
#include "SDL.h"
#include "ascii_key.h"
#include "bool.h"
#include "screen.h"
#include "fonts.h"
#include "text.h"
#include "term.h"

int x_offset(int col);
int y_offset(int row);

static term_screen ts;

static int row, col;
static int maxrow = 24;
static int maxcol = 80;

static int x_home = 6;
static int y_home = 3;
static int char_width = 10;
static int char_heigth = 13;
static int vert_space = 6;

static int term_fg_color;
static int term_bg_color;

bool clear_screen_flag = FALSE;

static int font;
static Uint32 bg;

void
term_init(int fn, Uint32 bg_color)
{
  int i;
  row = col = 0;

  for (i = 0; i < maxrow; i++)
    ts[i].len = 0;

  font = fn;
  bg = bg_color;

//  printf("term_init(): font = %d\n", font);
//  printf("term_init(): bg = %d\n", bg);

}

void
term_debug(void)
{
  int i, j, len;

  printf("--\n");

  for (i = 0; i < maxrow; i++)
  {
    len = ts[i].len;

    for (j = 0; j < len; j++)
      putchar(ts[i].tc[j].c);

    printf("\n");
  }

  printf("--\n");
}

void
increment_row(void)
{
  row++;

  if (row > maxrow - 1)
  {
//    term_clear();
    clear_screen_flag = TRUE;
    return;
  }

  col = 0;
}

void
term_clear(void)
{
  int i;

  row = col = 0;

  for (i = 0; i < maxrow; i++)
    ts[i].len = 0;

  clear_screen(bg);
}

void
term_put_char(int c)
{
//  printf("term_put_char(): c = %d\n", c);

  if (clear_screen_flag)
  {
    term_clear();
    clear_screen_flag = FALSE;
  }

  if (c == LF)
  {
    increment_row();
    return;
  }
  else if (c == BS)
  {
    int x, y;

    if (row == 0 && col == 0)
      return;

    ts[row].len = ts[row].len - 1;

    col--;

    if (col < 0)
    {
      row--;
      col = maxcol - 1;
    }

    x = x_offset(col);
    y = y_offset(row);

//    inverse_colors()
    draw_rectangle(x, y, char_width, 19, bg);
//    inverse_colors();

    return;
  }
  else
  {
    ts[row].tc[col].c = c;
//    ts[row].tc[col].fg_color = term_fg_color;
//    ts[row].tc[col].bg_color = term_bg_color;
    ts[row].len++;

    term_draw_char(row, col);

    col++;

    if (col >= maxcol)
      increment_row();
  }
}

void
term_draw_char(int row, int col)
{
  int x, y;
  glyphFont gf;

//  printf("term_draw_char(): row = %d, col = %d\n", row, col);
//  printf("term_draw_char(): font = %d\n", font);

  gf = get_font(font);

  x = x_offset(col);
  y = y_offset(row);

//  printf("term_draw_char(): x = %d, y = %d\n", x, y);

  draw_rectangle(x, y + vert_space, char_width, char_heigth + vert_space, bg);
//  set_fg_color(ts[row].tc[col].fg_color);

  draw_char(&gf, ts[row].tc[col].c, x, y);
}

void
term_show_cursor(void)
{
  int x, y;

  x = x_offset(col);
  y = y_offset(row);

  draw_rectangle(x, y + 2, 2, 22, bg);
}

void
term_clear_cursor(void)
{
  int x, y;

  x = x_offset(col);
  y = y_offset(row);

  printf("x = %d\n", x);
  printf("y = %d\n", y);

  draw_rectangle(x, y + 2, 2, 22, bg);
}

void
term_reverse_video(void)
{
  int tmp_color;

  tmp_color = term_fg_color;
  term_fg_color = term_bg_color;
  term_bg_color = tmp_color;
}

void
term_set_max(int x, int y)
{
  if (x > 0 && x < MAXROW)
    maxrow = x;

  if (y > 0 && y < MAXCOL)
    maxcol = y;
}

void
term_set_location(int x, int y)
{
  if (x >= 0 && x <= maxrow)
    row = x;

  if (y >= 0 && y <= maxcol)
    col = y;
}

int
x_offset(int col)
{
  return((char_width * col) + x_home);
}

int
y_offset(int row)
{
//  int i = char_heigth + vert_space + y_home; /* 19 */

//  return((i * row) + y_home + (2 * vert_space) + char_heigth);
  return(((char_heigth + vert_space) * row) + y_home);
}

void
term_print(char *s)
{
  int i, s_len;

  s_len = strlen(s);

  for (i = 0; i < s_len; i++)
    term_put_char(*s++);
}

