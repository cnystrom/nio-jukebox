/*
 *     mouse_test.c
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

#include "nio_lib.h"

void mouse_test_init(void);

int black;
int white;
int font;

int
main(int argc, char *argv[])
{
  int cls_flag = 1;

  nio_app_init("mouse_test", "0.1");

  black = nio_get_color("black");
  white = nio_get_color("white");

  font = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    black,
    white);

  mouse_test_init();

  while(1) {

//    int color;
//    nio_point p;
    mouse_state ms;

//    color = nio_get_rand_color();

    ms = nio_mouse_state();

    if (ms.b1 == PRESSED) {
      if (ms.x > 630)
        ms.x = 630;

      if (ms.y > 470)
        ms.y = 470;

      nio_draw_rectangle_rand(ms.x, ms.y, 10, 10);
      cls_flag = 1;  // Draw first before clearing screen again.
    }

    if (ms.b2 == PRESSED) {
      if (cls_flag) {
        mouse_test_init();
      }

      cls_flag = 0;
    }

    if (ms.b3 == PRESSED) {
      nio_exit();
      exit(0);
    }
  }
}

void
mouse_test_init(void)
{
  nio_clear_screen(white);

  nio_term_init(font, white);

  nio_print("\nNIO Mouse Test version 0.01\n");
 
  nio_print("\ndraw with button1, erase with button 2, exit with button 3\n");
}
