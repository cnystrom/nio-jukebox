/*
 *    func_num.c
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

#include <stdio.h>
#include "../nio_lib/nio.h"

void
print_func(int fn)
{
  if (fn == NIO_INIT) {
    printf("nio_init()\n");
  }
  else if (fn == NIO_EXIT) {
    printf("nio_exit()\n");
  }
  else if (fn == NIO_CHAR_TO_STDOUT) {
    printf("nio_char_to_stdout()\n");
  }
  else if (fn == NIO_INT_TO_STDOUT) {
    printf("nio_int_to_stdout()\n");
  }
  else if (fn == NIO_GET_CHAR) {
    printf("nio_get_char()\n");
  }
  else if (fn == NIO_PUT_CHAR) {
    printf("nio_put_char()\n");
  }
/*  else if (fn == NIO_MOUSE_BUTTON1) {
    printf("nio_mouse_button1()\n");
  }
  else if (fn == NIO_MOUSE_BUTTON2) {
    printf("nio_mouse_button2()\n");
  }
  else if (fn == NIO_MOUSE_BUTTON3) {
    printf("nio_mouse_button3()\n");
  }
  else if (fn == NIO_MOUSE_XY) {
    printf("nio_mouse_xy()\n");
  } */
  else if (fn == NIO_MOUSE_STATE) {
    printf("nio_mouse_state()\n");
  }
  else if (fn == NIO_SYSTEM_LOCAL) {
    printf("nio_system_local()\n");
  }
  else if (fn == NIO_GET_COLOR) {
    printf("nio_get_color()\n");
  }
  else if (fn == NIO_GET_COLOR_RGB) {
    printf("nio_get_color_rgb()\n");
  }
  else if (fn == NIO_GET_RAND_COLOR) {
    printf("nio_get_rand_color()\n");
  }
  else if (fn == NIO_LOAD_FONT) {
    printf("nio_load_font()\n");
  }
  else if (fn == NIO_LOAD_SYS_FONT) {
    printf("nio_load_sys_font()\n");
  }
  else if (fn == NIO_FREE_FONT) {
    printf("nio_free_font()\n");
  }
  else if (fn == NIO_DRAW_TEXT) {
    printf("nio_draw_text()\n");
  }
  else if (fn == NIO_SET_SCREEN) {
    printf("nio_set_screen()\n");
  }
  else if (fn == NIO_CLEAR_SCREEN) {
    printf("nio_clear_screen()\n");
  }
  else if (fn == NIO_DRAW_RECTANGLE) {
    printf("nio_draw_rectangle()\n");
  }
  else if (fn == NIO_DRAW_RECTANGLE_RGB) {
    printf("nio_draw_rectangle_rgb()\n");
  }
  else if (fn == NIO_DRAW_RECTANGLE_RAND) {
    printf("nio_draw_rectangle_rand()\n");
  }
  else if (fn == NIO_DRAW_POINT) {
    printf("nio_draw_point()\n");
  }
  else if (fn == NIO_DRAW_POINT_RGB) {
    printf("nio_draw_point_rgb()\n");
  }
  else if (fn == NIO_DRAW_POINT_RAND) {
    printf("nio_draw_point_rand()\n");
  }
  else if (fn == NIO_DRAW_LINE) {
    printf("nio_draw_line()\n");
  }
  else if (fn == NIO_DRAW_LINE_RGB) {
    printf("nio_draw_line_rgb()\n");
  }
  else if (fn == NIO_DRAW_LINE_RAND) {
    printf("nio_draw_line_rand()\n");
  }
  else if (fn == NIO_DRAW_ARC) {
    printf("nio_draw_arc()\n");
  }
  else if (fn == NIO_DRAW_ARC_RGB) {
    printf("nio_draw_arc_rgb()\n");
  }
  else if (fn == NIO_DRAW_ARC_RAND) {
    printf("nio_draw_arc_rand()\n");
  }
  else if (fn == NIO_SOUND) {
    printf("nio_sound()\n");
  }
  else if (fn == NIO_BEEP) {
    printf("nio_beep()\n");
  }
  else if (fn == NIO_LOAD_MUSIC) {
    printf("nio_load_music()\n");
  }
  else if (fn == NIO_PLAY_MUSIC) {
    printf("nio_play_music()\n");
  }
  else if (fn == NIO_STOP_MUSIC) {
    printf("nio_stop_music()\n");
  }
  else if (fn == NIO_MUSIC_PLAYING) {
    printf("nio_music_playing()\n");
  }
  else if (fn == NIO_LOAD_SOUND) {
    printf("nio_load_sound()\n");
  }
  else if (fn == NIO_PLAY_SOUND) {
    printf("nio_play_sound()\n");
  }
  else if (fn == NIO_FREE_SOUND) {
    printf("nio_free_sound()\n");
  }
  else if (fn == NIO_LOAD_IMAGE) {
    printf("nio_load_image()\n");
  }
  else if (fn == NIO_DRAW_IMAGE) {
    printf("nio_draw_image()\n");
  }
  else if (fn == NIO_FREE_IMAGE) {
    printf("nio_free_image()\n");
  }
  else if (fn == NIO_TERM_INIT) {
    printf("nio_term_init()\n");
  }
  else if (fn == NIO_PRINT) {
    printf("nio_print()\n");
  }
  else {
    printf("unknown function: %d\n", fn);
  }
}

