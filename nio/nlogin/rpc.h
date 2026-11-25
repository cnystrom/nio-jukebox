/*
 *    rpc.h
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

#ifndef _NIO_RPC_H
#define _NIO_RPC_H

#ifndef STR_LEN
#define STR_LEN  (256)
#endif

#ifndef BUF_SIZE
#define BUF_SIZE  (8192)
#endif

void nio_app_init_1(void);
void nio_exit_1(void);

void nio_char_to_stdout_1(void);
void nio_string_to_stdout_1(void);
void nio_int_to_stdout_1(void);

void nio_put_char_1(void);
void nio_get_char_1(void);

void nio_mouse_button1_1(void);
void nio_mouse_button2_1(void);
void nio_mouse_button3_1(void);
void nio_mouse_xy_1(void);
void nio_mouse_state_1(void);

void nio_system_local_1(void);

void nio_get_color_1(void);
void nio_get_color_rgb_1(void);
void nio_get_rand_color_1(void);

void nio_load_font_1(void);
void nio_load_sys_font_1(void);
void nio_free_font_1(void);
void nio_draw_text_1(void);

void nio_set_screen_1(void);
void nio_clear_screen_1(void);

void nio_draw_rectangle_1(void);
void nio_draw_rectangle_rgb_1(void);
void nio_draw_rectangle_rand_1(void);
void nio_draw_point_1(void);
void nio_draw_point_rgb_1(void);
void nio_draw_point_rand_1(void);
void nio_draw_line_1(void);
void nio_draw_line_rgb_1(void);
void nio_draw_line_rand_1(void);
void nio_draw_arc_1(void);
void nio_draw_arc_rgb_1(void);
void nio_draw_arc_rand_1(void);

void nio_sound_1(void);
void nio_beep_1(void);
void nio_load_music_1(void);
void nio_play_music_1(void);
void nio_stop_music_1(void);
void nio_music_playing_1(void);

void nio_load_sound_1(void);
void nio_play_sound_1(void);
void nio_free_sound_1(void);

void nio_load_image_1(void);
void nio_draw_image_1(void);
void nio_free_image_1(void);

void nio_term_init_1(void);
void nio_print_1(void);

#endif /* _NIO_RPC_H */

