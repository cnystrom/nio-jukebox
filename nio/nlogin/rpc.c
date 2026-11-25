/*
 *    rpc.c
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

#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "../new_rpc/buffer.h"
#include "../new_rpc/new_rpc.h"
//#include "nio_lib.h"
#include "file_xfr.h"
#include "playlib.h"
#include "sound.h"
#include "nio_sdl.h"
#include "screen.h"
#include "mouse.h"
#include "keyboard.h"
#include "fonts.h"
#include "colors.h"
#include "term.h"
#include "text.h"
#include "images.h"
#include "rpc.h"

static int sound = ON;

// Control Functions

void
nio_app_init_1(void)
{
  char nio_ver[STR_LEN];
  char server[STR_LEN];
  char app_name[STR_LEN];
  char app_ver[STR_LEN];
  char cwd[STR_LEN];

//  printf("Initializing remote application...\n");

  unpack_string(nio_ver);
  unpack_string(server);
  unpack_string(app_name);
  unpack_string(app_ver);
  unpack_string(cwd);

  init_file_loader(server, app_name, app_ver, cwd);

/*
  printf("nio_init_1:\n");
  printf(" nio_ver = %s\n", nio_ver);
  printf(" server = %s\n", server);
  printf(" app_name = %s\n", app_name);
  printf(" app_ver = %s\n", app_ver);
  printf(" cwd = %s\n", cwd);
*/

//  bg = get_color("black");

//  term_init(0, bg);

//  clear_screen(bg);

  nrpc_std_response();
}

void
nio_exit_1(void)
{
//  term_clear();

//  printf("nio_exit(): Program terminated at server.\n");

  nrpc_std_response();
}

// STDIO Function

void
nio_char_to_stdout_1(void)
{
  int c;

  c = unpack_int32();
  putchar(c);
  fflush(stdout);
  nrpc_std_response();
}

void
nio_string_to_stdout_1(void)
{
  char s[BUF_SIZE];

  unpack_string(s);

  printf(s);
  fflush(stdout);

  nrpc_std_response();
}

void
nio_int_to_stdout_1(void)
{
  int i;
  
  i = unpack_int32();

  printf("%d", i);
  fflush(stdout);

  nrpc_std_response();
}

// I/O Functions

void
nio_get_char_1(void)
{
  reset_buf();
  pack_int32(get_char());
  nrpc_send_response();
}

void
nio_put_char_1(void)
{
  int i;

  i = unpack_int32();

  term_put_char(i);
//  update_screen();

  nrpc_std_response();
}

// Mouse I/O Functions

/*
void
nio_mouse_button1_1(void)
{
  int mb1;

  reset_buf();
  mb1 = mouse_button_get(1);
  pack_int32(mb1);
  nrpc_send_response();
}

void
nio_mouse_button2_1(void)
{
  int mb2;

  reset_buf();
  mb2 = mouse_button_get(2);
  pack_int32(mb2);
  nrpc_send_response();
}

void
nio_mouse_button3_1(void)
{
  int mb3;

  reset_buf();
  mb3 = mouse_button_get(3);
  pack_int32(mb3);
  nrpc_send_response();
}

void
nio_mouse_xy_1(void)
{
  point_t mp;

  reset_buf();
  mp = mouse_get_xy();
  pack_int32(mp.x);
  pack_int32(mp.y);
  nrpc_send_response();
}
*/

void
nio_mouse_state_1(void)
{
  int mb;
  point_t mp;

  reset_buf();

  mb = mouse_button_get(1);
  pack_int32(mb);

  mb = mouse_button_get(2);
  pack_int32(mb);

  mb = mouse_button_get(3);
  pack_int32(mb);

  mp = mouse_get_xy();
  pack_int32(mp.x);
  pack_int32(mp.y);

  nrpc_send_response();
}

// System Command Functions

void
nio_system_local_1(void)
{
  char s[BUF_SIZE];

  unpack_string(s);

  system(s);
  fflush(stdout);

  nrpc_std_response();
}

// Color Functions

void
nio_get_color_1(void)
{
  int color;
  char s[BUF_SIZE];

  unpack_string(s);
//  fprintf(stderr, "nio_get_color_1(): s = %s\n", s);

  reset_buf();
  color = get_color(s);
//  fprintf(stderr, "nio_get_color_1(): color = %d\n", color);

  pack_int32(color);
  nrpc_send_response();
}

void
nio_get_color_rgb_1(void)
{
  int red, green, blue, color;

  red = unpack_int32();
  green = unpack_int32();
  blue = unpack_int32();
  reset_buf();
  color = get_color_rgb(red, green, blue);
  pack_int32(color);
  nrpc_send_response();
}

void
nio_get_rand_color_1(void)
{
  int color;

  reset_buf();
  color = get_rand_color();
  pack_int32(color);
  nrpc_send_response();
}

// Font Functions

void
nio_load_font_1(void)
{
  char fontfile[BUF_SIZE];
  int point_size;
  int style;
  int fg_color;
  int bg_color;
  int font_num;

  unpack_string(fontfile);
  point_size = unpack_int32();
  style = unpack_int32();
  fg_color = unpack_int32();
  bg_color = unpack_int32();

  reset_buf();
  font_num = load_font(load_file(fontfile), point_size, style, fg_color, bg_color);
  
  pack_int32(font_num);
  nrpc_send_response();
}

void
nio_load_sys_font_1(void)
{
  int sys_font;
  int point_size;
  int style;
  int fg_color;
  int bg_color;
  int font_num;

  sys_font = unpack_int32();
  point_size = unpack_int32();
  style = unpack_int32();
  fg_color = unpack_int32();
  bg_color = unpack_int32();

  reset_buf();
  font_num = load_sys_font(sys_font, point_size, style, fg_color, bg_color);
  
  pack_int32(font_num);
  nrpc_send_response();
}

void
nio_free_font_1(void)
{
  int font_num;

  font_num = unpack_int32();
  free_font(font_num);
  nrpc_std_response();
}

void
nio_draw_text_1(void)
{
  int font_num, x, y;
  char s[BUF_SIZE];
  glyphFont gf;

  font_num = unpack_int32();
  x = unpack_int32();
  y = unpack_int32();
  unpack_string(s);

  gf = get_font(font_num);

  draw_text(&gf, s, x, y);

  nrpc_std_response();
}

// Screen Functions

void
nio_set_screen_1(void)
{
  int x, y, color;

  x = unpack_int32();
  y = unpack_int32();
  color = unpack_int32();

  init_screen(x, y, SDL_ANYFORMAT);
  clear_screen(color);

  nrpc_std_response();
}

void
nio_clear_screen_1(void)
{
  int color;

//  term_clear();
  color = unpack_int32();
  clear_screen(color);
  nrpc_std_response();
}

// Drawing Functions

void
nio_draw_rectangle_1(void)
{
  int x, y, width, height, color;
  char s[BUFSIZ];

  x = unpack_int32();
  y = unpack_int32();
  width = unpack_int32();
  height = unpack_int32();
  unpack_string(s);

  color = get_color(s);

  draw_rectangle(x, y, width, height, color);

  nrpc_std_response();
}

void
nio_draw_rectangle_rgb_1(void)
{
  int x, y, width, height, r, g, b, color;

  x = unpack_int32();
  y = unpack_int32();
  width = unpack_int32();
  height = unpack_int32();
  r = unpack_int32();
  g = unpack_int32();
  b = unpack_int32();

  color = get_color_rgb(r, b, g);

  draw_rectangle(x, y, width, height, color);

  nrpc_std_response();
}

void
nio_draw_rectangle_rand_1(void)
{
  int x, y, width, height, color;

  x = unpack_int32();
  y = unpack_int32();
  width = unpack_int32();
  height = unpack_int32();

  color = get_rand_color();

  draw_rectangle(x, y, width, height, color);

  nrpc_std_response();
}

void
nio_draw_point_1(void)
{
  int x, y, color;
  char s[BUFSIZ];

  x = unpack_int32();
  y = unpack_int32();
  unpack_string(s);

  color = get_color(s);

  draw_point(x, y, color);

  nrpc_std_response();
}

void
nio_draw_point_rgb_1(void)
{
  int x, y, r, g, b, color;

  x = unpack_int32();
  y = unpack_int32();
  r = unpack_int32();
  g = unpack_int32();
  b = unpack_int32();

  color = get_color_rgb(r, g, b);

  draw_point(x, y, color);

  nrpc_std_response();
}

void
nio_draw_point_rand_1(void)
{
  int x, y, color;

  x = unpack_int32();
  y = unpack_int32();

  color = get_rand_color();

  draw_point(x, y, color);

  nrpc_std_response();
}

void
nio_draw_line_1(void)
{
  int x1, y1, x2, y2, color;
  char s[BUFSIZ];

  x1 = unpack_int32();
  y1 = unpack_int32();
  x2 = unpack_int32();
  y2 = unpack_int32();
  unpack_string(s);

  color = get_color(s);

  draw_line(x1, y1, x2, y2, color);

  nrpc_std_response();
}

void
nio_draw_line_rgb_1(void)
{
  int x1, y1, x2, y2, r, g, b, color;

  x1 = unpack_int32();
  y1 = unpack_int32();
  x2 = unpack_int32();
  y2 = unpack_int32();

  r = unpack_int32();
  g = unpack_int32();
  b = unpack_int32();

  color = get_color_rgb(r, g, b);

  draw_line(x1, y1, x2, y2, color);

  nrpc_std_response();
}

void
nio_draw_line_rand_1(void)
{
  int x1, y1, x2, y2, color;

  x1 = unpack_int32();
  y1 = unpack_int32();
  x2 = unpack_int32();
  y2 = unpack_int32();

  color = get_rand_color();

  draw_line(x1, y1, x2, y2, color);

  nrpc_std_response();
}

void
nio_draw_arc_1(void)
{
  int x, y, radius, color;
  char s[BUFSIZ];

  x = unpack_int32();
  y = unpack_int32();
  radius = unpack_int32();
  unpack_string(s);

  color = get_color(s);

  draw_arc(x, y, radius, color);

  nrpc_std_response();
}

void
nio_draw_arc_rgb_1(void)
{
  int x, y, radius, r, g, b, color;

  x = unpack_int32();
  y = unpack_int32();
  radius = unpack_int32();
  r = unpack_int32();
  g = unpack_int32();
  b = unpack_int32();

  color = get_color_rgb(r, g, b);

  draw_arc(x, y, radius, color);

  nrpc_std_response();
}

void
nio_draw_arc_rand_1(void)
{
  int x, y, radius, color;

  x = unpack_int32();
  y = unpack_int32();
  radius = unpack_int32();

  color = get_rand_color();

  draw_arc(x, y, radius, color);

  nrpc_std_response();
}

// Sound Functions

void
nio_sound_1(void)
{
  sound = unpack_int32();
  nrpc_std_response();
}

void
nio_beep_1(void)
{
  if (sound) {
    putchar(7);
    printf("beep - sound\n");
  }
  else {
    printf("beep - no sound\n");
  }

  nrpc_std_response();
}

void
nio_load_music_1(void)
{
  char filename[BUF_SIZE];

  unpack_string(filename);

  if (audio_avail()) {
    load_music(load_file(filename));
  }
 
  nrpc_std_response();
}

void
nio_play_music_1(void)
{
  int loops;

  loops = unpack_int32();

  if (sound) {
    play_music(loops);
  }
  else
    printf("Sound is off...\n");

  nrpc_std_response();
}

void
nio_stop_music_1(void)
{
  stop_music();
  nrpc_std_response();
}

void
nio_music_playing_1(void)
{
  bool b;

  reset_buf();
  b = music_playing();
  pack_int32(b);
  nrpc_send_response();
}

void
nio_load_sound_1(void)
{
  int sound_num;
  char filename[BUF_SIZE];

  unpack_string(filename);

//  printf("nio_load_sound(): filename = %s\n", filename);

  reset_buf();

  if (audio_avail()) {
    sound_num = load_sound(load_file(filename));
  }
  else {
    sound_num = -1;
  }

//  printf("nio_load_sound(): sound_num = %d\n", sound_num);
 
  pack_int32(sound_num);

  nrpc_send_response();
}

void
nio_play_sound_1(void)
{
  int channel, sound_num, loops;

  sound_num = unpack_int32();
  loops = unpack_int32();

  if (sound) {
    if (sound_num >= 0) {
      channel = play_sound(sound_num, loops);

//      printf("nio_play_sound_1(): channel = %d\n", channel);

      if (channel >= 0) {
        while(! sound_channel_done(channel))
          ;
      }
    }
  }
  else
    printf("Sound is off...\n");

  nrpc_std_response();
}

void
nio_free_sound_1(void)
{
  int sound_num;

  sound_num = unpack_int32();

  delete_sound(sound_num);
  nrpc_std_response();
}

// Image Functions

void
nio_load_image_1(void)
{
  int image_num;

  char filename[BUF_SIZE];

  unpack_string(filename);

  reset_buf();
  image_num = load_image(load_file(filename));
 
  pack_int32(image_num);

  nrpc_send_response();
}

void
nio_draw_image_1(void)
{
  int i_num, x, y;

  i_num = unpack_int32();
  x = unpack_int32();
  y = unpack_int32();

  draw_image(i_num, x, y);

  nrpc_std_response();
}

void
nio_free_image_1(void)
{
  int image_num;

  image_num = unpack_int32();

  free_image(image_num);
  nrpc_std_response();
}

void
nio_term_init_1(void)
{
  int font_num;
  int color;

  font_num = unpack_int32();
  color = unpack_int32();
  term_init(font_num, color);
  nrpc_std_response();
}

void
nio_print_1(void)
{
  int i, s_len;
  char s[BUF_SIZE];

  unpack_string(s);

//  printf("nio_print_1(): s = |%s|\n", s);

  s_len = strlen(s);

//  printf("nio_print_1(): s_len = %d\n", s_len);
 
 for (i = 0; i < s_len; i++)
   term_put_char(s[i]);

  nrpc_std_response();
}

