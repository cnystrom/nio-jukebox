/*
 *    mainloop.c
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
#include <stdlib.h>
#include "SDL.h"
#include "../new_rpc/new_rpc.h"
#include "../nio_lib/nio.h"
#include "nio_sdl.h"
#include "rpc.h"
#include "print_func.h"

void
nio_client_main_loop(void)
{
  for (;;)
  {
    int func_num;

    sdl_handle_event();

//    printf("Getting function...\n");

    func_num = nrpc_get_function();

//    print_func(func_num);

//    printf("func_num = %d\n", func_num);

    if (func_num == NRPC_INVALID)
    {
      ;
//      printf("NRPC_INVALID rcvd\n");
    }
    else if (func_num == NRPC_EXIT)
    {
      printf("Exit command rcvd.\n");
      break;
    }
    else if (func_num == NRPC_REVERSE)
    {
      printf("Reverse command rcvd.\n");
      nrpc_exit();
      break;
    }
    else if (func_num == NIO_INIT)
      nio_app_init_1();
    else if (func_num == NIO_EXIT)
    {
      nio_exit_1();
      break;
    }
    else if (func_num == NIO_CHAR_TO_STDOUT)
      nio_char_to_stdout_1();
    else if (func_num == NIO_STRING_TO_STDOUT)
      nio_string_to_stdout_1();
    else if (func_num == NIO_INT_TO_STDOUT)
      nio_int_to_stdout_1();
    else if (func_num == NIO_GET_CHAR)
      nio_get_char_1();
    else if (func_num == NIO_PUT_CHAR)
      nio_put_char_1();
/*    else if (func_num == NIO_MOUSE_BUTTON1)
      nio_mouse_button1_1();
    else if (func_num == NIO_MOUSE_BUTTON2)
      nio_mouse_button2_1();
    else if (func_num == NIO_MOUSE_BUTTON3)
      nio_mouse_button3_1();
    else if (func_num == NIO_MOUSE_XY)
      nio_mouse_xy_1(); */
    else if (func_num == NIO_MOUSE_STATE)
      nio_mouse_state_1();
    else if (func_num == NIO_SYSTEM_LOCAL)
      nio_system_local_1();
    else if (func_num == NIO_GET_COLOR)
      nio_get_color_1();
    else if (func_num == NIO_GET_COLOR_RGB)
      nio_get_color_rgb_1();
    else if (func_num == NIO_GET_RAND_COLOR)
      nio_get_rand_color_1();
    else if (func_num == NIO_LOAD_FONT)
      nio_load_font_1();
    else if (func_num == NIO_LOAD_SYS_FONT)
      nio_load_sys_font_1();
    else if (func_num == NIO_FREE_FONT)
      nio_free_font_1();
    else if (func_num == NIO_DRAW_TEXT)
      nio_draw_text_1();
    else if (func_num == NIO_CLEAR_SCREEN)
      nio_clear_screen_1();
    else if (func_num == NIO_DRAW_RECTANGLE)
      nio_draw_rectangle_1();
    else if (func_num == NIO_DRAW_RECTANGLE_RGB)
      nio_draw_rectangle_rgb_1();
    else if (func_num == NIO_DRAW_RECTANGLE_RAND)
      nio_draw_rectangle_rand_1();
    else if (func_num == NIO_DRAW_POINT)
      nio_draw_point_1();
    else if (func_num == NIO_DRAW_POINT_RGB)
      nio_draw_point_rgb_1();
    else if (func_num == NIO_DRAW_POINT_RAND)
      nio_draw_point_rand_1();
    else if (func_num == NIO_DRAW_LINE)
      nio_draw_line_1();
    else if (func_num == NIO_DRAW_LINE_RGB)
      nio_draw_line_rgb_1();
    else if (func_num == NIO_DRAW_LINE_RAND)
      nio_draw_line_rand_1();
    else if (func_num == NIO_DRAW_ARC)
      nio_draw_arc_1();
    else if (func_num == NIO_DRAW_ARC_RGB)
      nio_draw_arc_rgb_1();
    else if (func_num == NIO_DRAW_ARC_RAND)
      nio_draw_arc_rand_1();
    else if (func_num == NIO_SOUND)
      nio_sound_1();
    else if (func_num == NIO_BEEP)
      nio_beep_1();
    else if (func_num == NIO_LOAD_MUSIC)
      nio_load_music_1();
    else if (func_num == NIO_PLAY_MUSIC)
      nio_play_music_1();
    else if (func_num == NIO_STOP_MUSIC)
      nio_stop_music_1();
    else if (func_num == NIO_MUSIC_PLAYING)
      nio_music_playing_1();
    else if (func_num == NIO_LOAD_SOUND)
      nio_load_sound_1();
    else if (func_num == NIO_PLAY_SOUND)
      nio_play_sound_1();
    else if (func_num == NIO_FREE_SOUND)
      nio_free_sound_1();
    else if (func_num == NIO_LOAD_IMAGE)
      nio_load_image_1();
    else if (func_num == NIO_DRAW_IMAGE)
      nio_draw_image_1();
    else if (func_num == NIO_FREE_IMAGE)
      nio_free_image_1();
    else if (func_num == NIO_TERM_INIT)
      nio_term_init_1();
    else if (func_num == NIO_PRINT)
      nio_print_1();
    else
    {
      printf("nio_client_main_loop(): bad function number = %d\n", func_num);
      exit(-1);
    }
  }
}

