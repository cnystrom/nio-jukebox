/*
 *    screen_test.c
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

int
main(int argc, char *argv[])
{
  int i, black, white, font;

  nio_app_init("screen_test", "0.1");

  black = nio_get_color("black");
  white = nio_get_color("white");

  nio_clear_screen(black);

  font = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    white,
    black);

  nio_term_init(font, black);

  for (i = 1; i < 10; i++)
    nio_printf("%d 3456789|123456789|123456789|123456789|123456789|123456789|123456789|1234567890", i);

  for (i = 10; i <= 24; i++)
    nio_printf("%d 456789|123456789|123456789|123456789|123456789|123456789|123456789|1234567890", i);

//  nio_print("25 456789|123456789|123456789|123456789|123456789|123456789|123456789|1234567890\n");

  nio_pause("");

  nio_exit();
  exit(0);
}
