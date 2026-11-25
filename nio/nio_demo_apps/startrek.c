/*
 *    startrek.c
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
  int black, white, font, image_num, sound_num;

  nio_app_init("startrek", "0.1");

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

  nio_print("\nNIO Star Trek version 0.01\n\n");

  image_num = nio_load_image("startrek/startrek.jpg");
  sound_num = nio_load_sound("startrek/c604.wav");

  nio_draw_image(image_num, 300, 75);
  nio_play_sound(sound_num, 0);

  nio_pause("Hit any key to continue...");

  nio_free_image(image_num);
  nio_free_sound(sound_num);

  nio_exit();
  exit(0);
}

