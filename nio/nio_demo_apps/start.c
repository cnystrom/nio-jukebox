/*
 *    list.c
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
#include "nio_lib.h"

void list(int color);

int
main(int argc, char *argv[])
{
  int black, white;
  int font;

  nio_app_init("list", "0.1");

  black = nio_get_color("black");
  white = nio_get_color("white");

  font = nio_load_sys_font(
    NIO_DEFAULT_FONT,
    NIO_DEFAULT_PTSIZE,
    NIO_STYLE_NORMAL,
    white,
    black);

  nio_term_init(font, black);

  list(black);

  while(TRUE) {
    nio_string s;

    nio_print("\nPROGRAM> ");
    nio_get_string(s, MAX_STR_LEN);

    if (strncmp(s, "exit", 4) == 0) {
      break;
    }

    system(s);

    list(black);
  }
  
  nio_free_font(font);

  nio_exit();
  exit(0);
}

void
list(int color)
{
  nio_clear_screen(color);

  nio_print("\nNIO List version 0.01\n");
  nio_print("Programs available:\n\n");
  nio_system_remote("cd /home/cnystrom/nio; ls -1 *.nio | sed 's/.nio//g'");
}

