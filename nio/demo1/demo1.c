/*
 *    demo1.c
 *
 *    Copyright (C) 2004  <Chris Nystrom>
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
 *              or cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#include "nio_lib.h"

#define MAX_MODE    (2)

void demo1_init(void);
void clear_screen(void);

int
main(int argc, char *argv[])
{
  int cls_flag = 1;
  int mode = 0;
  int mode_flag = 1;

  nio_app_init("demo1", "0.1");

  demo1_init();

  while(1)
  {
    int x, y;
    mouse_state ms;

//    color = nio_get_rand_color();

    x = nio_rand_int(640);
    y = nio_rand_int(480);

    if (0 == mode) {
      nio_draw_rectangle_rand(x, y, 10, 10);
    }
    if (1 == mode) {
      nio_draw_arc_rand(x, y, 10);
    }
    if (2 == mode) {
      int x2, y2;

      x2 = nio_rand_int(640);
      y2 = nio_rand_int(480);

      nio_draw_line_rand(x, y, x2, y2);
    }

    ms = nio_mouse_state();

    if (ms.b1) {
      if (mode_flag) {
        mode++;

        if (mode > MAX_MODE) {
          mode = 0;
        }

        mode_flag = 0;
      }
      cls_flag = 1;
    } else {
      mode_flag = 1;
    }

    if (ms.b2) {
      if (cls_flag) {
        clear_screen();
        cls_flag = 0;
      }
      mode_flag = 1;
    } else {
      cls_flag = 1;
    }

    if (ms.b3) {
      nio_stop_music();
      nio_exit();
      exit(0);
    }
  }
}

void
demo1_init(void)
{
  int black, white, font;

  black = nio_get_color("black");
  white = nio_get_color("white");

//  nio_clear_screen(black);

  font = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    white,
    black);

  nio_load_music("demo1/Rome_Italy.ogg");

  nio_term_init(font, black);

  nio_print("\nDEMO1 version 0.01\n");

  nio_play_music(0);
}

void
clear_screen(void)
{
  nio_draw_rectangle_rand(1, 1, 640, 480);
}

