/*
 *    nio_lib.c
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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef UNIX
#include <sys/param.h>
#endif
#include <stdarg.h>
#include <time.h>
#include "nio.h"
#include "ascii_key.h"
#include "../misc_lib/wlog.h"
#include "../new_rpc/buffer.h"
#include "../new_rpc/new_rpc.h"
#include "nio_lib.h"

#define SYSTEM_BUFFER    (24*80*10)  // 10 Terminals full enough?

#ifndef BUFSIZ
#define BUFSIZ (8192)
#endif

// Control Functions

void
nio_app_init(char *app_name, char *app_ver)
{
  char nio_ver[8] = NIO_LIB_VER;
  char hostname[MAXHOSTNAMELEN];
  char cwd[256];
  char s[BUFSIZ];

  snprintf(s, BUFSIZ, "/var/tmp/%s.%s.log", app_name, app_ver);
  wlog_open_file(s);
  wlog("nio_app_init(): log file opened.\n");

  nrpc_init_server();

  gethostname(hostname, MAXHOSTNAMELEN);
  getcwd(cwd, 256);

  nrpc_set_function(NIO_INIT);

  pack_string(nio_ver);
  pack_string(hostname);
  pack_string(app_name);
  pack_string(app_ver);
  pack_string(cwd);

//  wlog("nio_app_init(): message packed.\n");

//  wlog("nio_app_init(): usleep(1000)..,\n");
//  usleep(10000);  // 1/100 second to sync networking

//  wlog("sending message...\n");
  nrpc_send_message();

//  wlog("nio_app_init(): message sent.\n");

  randomize();
}

void
nio_exit(void)
{
//  printf("nio_exit() called.\n");

  nrpc_set_function(NIO_EXIT);
  nrpc_send_message();
  wlog_close();
}

// stdio Functions

void
nio_char_to_stdout(int c)
{
  nrpc_set_function(NIO_CHAR_TO_STDOUT);
  pack_int32(c);
  nrpc_send_message();
}

void
nio_string_to_stdout(char *s)
{
  nrpc_set_function(NIO_STRING_TO_STDOUT);
  pack_string(s);
  nrpc_send_message();
}

void
nio_int_to_stdout(int i)
{
  nrpc_set_function(NIO_INT_TO_STDOUT);
  pack_int32(i);
  nrpc_send_message();
}

void
nio_printf_to_stdout(char *format, ...)
{
  nio_string s;
  va_list ap;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  nio_string_to_stdout(s);
}

// io Functions

int
nio_get_char(bool b)
{
  int c = NUL;

  nrpc_set_function(NIO_GET_CHAR);
  nrpc_send_message();

  c  = unpack_int32();

  if (b == TRUE)
    nio_put_char(c);

  return(c);
}

void
nio_put_char(int c)
{
  nrpc_set_function(NIO_PUT_CHAR);
  pack_int32(c);
  nrpc_send_message();
}

int
nio_get_string(char *s, int lim)
{
  int c, i = 0;

  c = nio_get_char(TRUE);

  while (lim > 0 && c != EOF && c != RET) {
    if (c == BS) {
      if (i != 0 ) {
        lim++;
        s[i--] = '\0';
      }
    }
    else {
      lim--;
      s[i++] = c;
    }
    c = nio_get_char(TRUE);
  }

  s[i] = '\0';

  return i;
}

void
nio_print(char *s)
{
  nrpc_set_function(NIO_PRINT);
  pack_string(s);

//  wlog("s = |%s|\n", s);

  nrpc_send_message();
}

void
nio_printf(char *format, ...)
{
  nio_string s;
  va_list ap;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  nio_print(s);
}

void
nio_input(char *s1, char *s2, int str_len)
{
  nio_print(s1);
  nio_get_string(s2, str_len);
  nio_print("\n");
}

void
nio_pause(char *s)
{
  nio_print(s);
  nio_get_char(FALSE);
}

// Mouse I/O Functions
/*
int
nio_mouse_button1(void)
{
  int i;

  nrpc_set_function(NIO_MOUSE_BUTTON1);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

int
nio_mouse_button2(void)
{
  int i;

  nrpc_set_function(NIO_MOUSE_BUTTON2);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

int
nio_mouse_button3(void)
{
  int i;

  nrpc_set_function(NIO_MOUSE_BUTTON3);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

nio_point
nio_mouse_xy(void)
{
  nio_point p;

  nrpc_set_function(NIO_MOUSE_XY);
  nrpc_send_message();
  p.x = unpack_int32();
  p.y = unpack_int32();
  return(p);
}
*/

mouse_state
nio_mouse_state(void)
{
  mouse_state ms;

  nrpc_set_function(NIO_MOUSE_STATE);
  nrpc_send_message();
  ms.b1 = unpack_int32();
  ms.b2 = unpack_int32();
  ms.b3 = unpack_int32();
  ms.x = unpack_int32();
  ms.y = unpack_int32();
  return(ms);
}

// System Command Functions

void
nio_system_local(char *s)
{
  nrpc_set_function(NIO_SYSTEM_LOCAL);
  pack_string(s);
  nrpc_send_message();
}

void
nio_system_remote(char *s)
{
  int fd, n;
  char s2[SYSTEM_BUFFER+64];

  wlog("nio_system_remote(): s = |%s|\n", s);

  strcpy(s2, s);

#ifdef WIN32
  strcat(s2, " > C:\TMP\nlogin.tmp");
#else
  strcat(s2, " > /usr/tmp/nlogin.tmp");
#endif

  n = strlen(s2);

  wlog("nio_system_remote(): executing: |%s|\n", s2);

  system(s2);

  s2[0] = 0x00;

#ifdef WIN32
  fd = open("C:\TMP\nlogin.tmp", O_RDONLY, 0);
#else
  fd = open("/usr/tmp/nlogin.tmp", O_RDONLY, 0);
#endif
  n = read(fd, &s2, SYSTEM_BUFFER);
  close(fd);

  s2[n] = 0x00;

  wlog("nio_system_remote(): results: |%s|\n", s2);

  nio_print(s2);
}

// Color Functions

int
nio_get_color(char *s)
{
  int i;

//  printf("nio_get_color(): s = %s\n", s);

  nrpc_set_function(NIO_GET_COLOR);
  pack_string(s);
  nrpc_send_message();
  i = unpack_int32();

//  printf("nio_get_color(): i = %d\n", i);
  return(i);
}

int
nio_get_color_rgb(int red, int green, int blue)
{
  int i;

  nrpc_set_function(NIO_GET_COLOR_RGB);
  pack_int32(red);
  pack_int32(green);
  pack_int32(blue);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

int
nio_get_rand_color(void)
{
  int i;

  nrpc_set_function(NIO_GET_RAND_COLOR);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

// Font Functions

int
nio_load_font(char *filename, int point_size, int style,
	       	int fg_color, int bg_color)
{
  int i;

  nrpc_set_function(NIO_LOAD_FONT);
  pack_string(filename);
  pack_int32(point_size);
  pack_int32(style);
  pack_int32(fg_color);
  pack_int32(bg_color);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

int
nio_load_sys_font(int system_font, int point_size, int style,
	       	int fg_color, int bg_color)
{
  int i;

  nrpc_set_function(NIO_LOAD_SYS_FONT);
  pack_int32(system_font);
  pack_int32(point_size);
  pack_int32(style);
  pack_int32(fg_color);
  pack_int32(bg_color);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

void
nio_free_font(int i)
{
  nrpc_set_function(NIO_FREE_FONT);
  pack_int32(i);
  nrpc_send_message();
}

void
nio_draw_text(int font_num, int x, int y, char *s)
{
  nrpc_set_function(NIO_DRAW_TEXT);
  pack_int32(font_num);
  pack_int32(x);
  pack_int32(y);
  pack_string(s);
  nrpc_send_message();
}

void
nio_draw_textf(int font_num, int x, int y, char *format, ...)
{
  nio_string s;
  va_list ap;

  va_start(ap, format);
  vsprintf(s, format, ap);
  va_end(ap);

  nio_draw_text(font_num, x, y, s);
}

// Screen Functions

void
nio_set_screen(int x, int y, int bg_color)
{
  nrpc_set_function(NIO_SET_SCREEN);
  pack_int32(x);
  pack_int32(y);
  pack_int32(bg_color);
  nrpc_send_message();
}

void
nio_clear_screen(int bg_color)
{
  nrpc_set_function(NIO_CLEAR_SCREEN);
  pack_int32(bg_color);
  nrpc_send_message();
}

// Drawing Functions

void
nio_draw_rectangle(int x, int y, int width, int height, char *color)
{
  nrpc_set_function(NIO_DRAW_RECTANGLE);
  pack_int32(x);
  pack_int32(y);
  pack_int32(width);
  pack_int32(height);
  pack_string(color);
  nrpc_send_message();
}

void
nio_draw_rectangle_rgb(int x, int y, int width, int height, int r, int g, int b)
{
  nrpc_set_function(NIO_DRAW_RECTANGLE_RGB);
  pack_int32(x);
  pack_int32(y);
  pack_int32(width);
  pack_int32(height);
  pack_int32(r);
  pack_int32(g);
  pack_int32(b);
  nrpc_send_message();
}

void
nio_draw_rectangle_rand(int x, int y, int width, int height)
{
  nrpc_set_function(NIO_DRAW_RECTANGLE_RAND);
  pack_int32(x);
  pack_int32(y);
  pack_int32(width);
  pack_int32(height);
  nrpc_send_message();
}

void
nio_draw_point(int x, int y, char *color)
{
  nrpc_set_function(NIO_DRAW_POINT);
  pack_int32(x);
  pack_int32(y);
  pack_string(color);
  nrpc_send_message();
}

void
nio_draw_point_rgb(int x, int y, int r, int g, int b)
{
  nrpc_set_function(NIO_DRAW_POINT_RGB);
  pack_int32(x);
  pack_int32(y);
  pack_int32(r);
  pack_int32(g);
  pack_int32(b);
  nrpc_send_message();
}

void
nio_draw_point_rand(int x, int y)
{
  nrpc_set_function(NIO_DRAW_POINT_RAND);
  pack_int32(x);
  pack_int32(y);
  nrpc_send_message();
}

void
nio_draw_line(int x1, int y1, int x2, int y2, char *color)
{
  nrpc_set_function(NIO_DRAW_LINE);
  pack_int32(x1);
  pack_int32(y1);
  pack_int32(x2);
  pack_int32(y2);
  pack_string(color);
  nrpc_send_message();
}

void
nio_draw_line_rgb(int x1, int y1, int x2, int y2, int r, int g, int b)
{
  nrpc_set_function(NIO_DRAW_LINE_RGB);
  pack_int32(x1);
  pack_int32(y1);
  pack_int32(x2);
  pack_int32(y2);
  pack_int32(r);
  pack_int32(g);
  pack_int32(b);
  nrpc_send_message();
}

void
nio_draw_line_rand(int x1, int y1, int x2, int y2)
{
  nrpc_set_function(NIO_DRAW_LINE_RAND);
  pack_int32(x1);
  pack_int32(y1);
  pack_int32(x2);
  pack_int32(y2);
  nrpc_send_message();
}

void
nio_draw_arc(int x, int y, int radius, char *color)
{
  nrpc_set_function(NIO_DRAW_ARC);
  pack_int32(x);
  pack_int32(y);
  pack_int32(radius);
  pack_string(color);
  nrpc_send_message();
}

void
nio_draw_arc_rgb(int x, int y, int radius, int r, int g, int b)
{
  nrpc_set_function(NIO_DRAW_ARC_RAND);
  pack_int32(x);
  pack_int32(y);
  pack_int32(radius);
  pack_int32(r);
  pack_int32(g);
  pack_int32(b);
  nrpc_send_message();
}

void
nio_draw_arc_rand(int x, int y, int radius)
{
  nrpc_set_function(NIO_DRAW_ARC_RAND);
  pack_int32(x);
  pack_int32(y);
  pack_int32(radius);
  nrpc_send_message();
}

// Sound Functions

void
nio_sound(int status)
{
  nrpc_set_function(NIO_SOUND);
  pack_int32(status);
  nrpc_send_message();
}

void
nio_beep(void)
{
  nrpc_set_function(NIO_BEEP);
  nrpc_send_message();
}

void
nio_load_music(char *filename)
{
  nrpc_set_function(NIO_LOAD_MUSIC);
  pack_string(filename);
  nrpc_send_message();
}

void
nio_play_music(int loops)
{
  nrpc_set_function(NIO_PLAY_MUSIC);
  pack_int32(loops);
  nrpc_send_message();
}

void
nio_stop_music(void)
{
  nrpc_set_function(NIO_STOP_MUSIC);
  nrpc_send_message();
}

bool
nio_music_playing(void)
{
  bool b;

  nrpc_set_function(NIO_MUSIC_PLAYING);
  nrpc_send_message();
  b = unpack_int32();
  return(b);
}

int
nio_load_sound(char *filename)
{
  int i;

  nrpc_set_function(NIO_LOAD_SOUND);
  pack_string(filename);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

void
nio_play_sound(int sound_num, int loops)
{
  nrpc_set_function(NIO_PLAY_SOUND);
  pack_int32(sound_num);
  pack_int32(loops);
  nrpc_send_message();
}

void
nio_free_sound(int i)
{
  nrpc_set_function(NIO_FREE_SOUND);
  pack_int32(i);
  nrpc_send_message();
}

// Image Functions

int
nio_load_image(char *filename)
{
  int i;

  nrpc_set_function(NIO_LOAD_IMAGE);
  pack_string(filename);
  nrpc_send_message();
  i = unpack_int32();
  return(i);
}

void
nio_draw_image(int x, int y, int image_num)
{
  nrpc_set_function(NIO_DRAW_IMAGE);
  pack_int32(x);
  pack_int32(y);
  pack_int32(image_num);
  nrpc_send_message();
}

void
nio_free_image(int i)
{
  nrpc_set_function(NIO_FREE_IMAGE);
  pack_int32(i);
  nrpc_send_message();
}

void
nio_term_init(int font_num, int color)
{
  nrpc_set_function(NIO_TERM_INIT);
  pack_int32(font_num);
  pack_int32(color);
  nrpc_send_message();
}

/********************************************************************/

/* Seed the randomizer with the timer */
void
randomize(void)
{
  time_t timer;
  srand ((unsigned) time (&timer));
}

/* Returns an integer from 0 to i */
int
nio_rand_int(int i)
{
  if (i <= 0)
  {
#ifdef DEBUG
//    printf("Error: nio_rand_int i <= 0.\n");
#endif
    return(0);
  }
  else
    return((int)(rand() % i) + .5);
}

bool
nio_rand_bool(void)
{
  bool b;

  if (nio_rand_int(100) < 50)
    b = TRUE;
  else
    b = FALSE;

  return(b);
}

