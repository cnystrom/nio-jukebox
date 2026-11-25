/*
 *    nio_lib.h
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

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#ifndef _NIO_LIB_H
#define _NIO_LIB_H

#ifndef _TYPES_H
#include "types.h"
#endif

#ifndef _NIO_FONT_H
#include "nio_font.h"
#endif

#ifndef _ASCII_KEY_H
#include "ascii_key.h"
#endif

#define NIO_LIB_VER  "0.04"

#ifndef EOF
#define EOF  (0)
#endif

#define MAX_STR_LEN   (256)

// Useful typedefs 

typedef char nio_string[MAX_STR_LEN];

typedef struct {
  int x;
  int y;
} nio_point;

typedef struct {
  int b1;
  int b2;
  int b3;
  int x;
  int y;
} mouse_state;

// *********** NIO Routines **********

// Control Functions

void nio_app_init(char *app_name, char *app_ver);
void nio_exit(void);

// stdio Functions

void nio_char_to_stdout(int c);
void nio_string_to_stdout(char *s);
void nio_int_to_stdout(int i);
void nio_printf_to_stdout(char *format, ...);

// I/O Functions

int  nio_get_char(bool b);
void nio_put_char(int c);

int  nio_get_string(char *s, int lim);

void nio_print(char *s);
void nio_printf(char *format, ...);

void nio_input(char *s1, char *s2, int str_len);

void nio_pause(char *s);

// Mouse I/O functions

//int nio_mouse_button1(void);
//int nio_mouse_button2(void);
//int nio_mouse_button3(void);

//nio_point nio_mouse_xy(void);
mouse_state nio_mouse_state(void);

// System Command Functions

void nio_system_local(char *s);
void nio_system_remote(char *s);

// Color Functions

int  nio_get_color(char *s);
int  nio_get_color_rgb(int red, int green, int blue);
int  nio_get_rand_color(void);

// Font Functions

int  nio_load_font(char *filename, int point_size, int style,
       	int fg_color, int bg_color);

int  nio_load_sys_font(int system_font, int point_size, int style,
       	int fg_color, int bg_color);

void nio_free_font(int font_num);

// Text Functions

void nio_draw_text(int font_num, int x, int y, char *s);
void nio_draw_textf(int font_num, int x, int y, char *format, ...);

// Screen functions

nio_point nio_get_screen_size(void);
void nio_set_screen(int x, int y, int bg_color);
void nio_clear_screen(int bg_color);

// Drawing functions

void nio_draw_rectangle(int x, int y, int width, int height, char *color);
void nio_draw_rectangle_rgb(int x, int y, int width, int height, int r, int g,
  int b);
void nio_draw_rectangle_rand(int x, int y, int width, int height);
void nio_draw_point(int x, int y, char *color);
void nio_draw_point_rgb(int x, int y, int r, int g, int b);
void nio_draw_point_rand(int x, int y);
void nio_draw_line(int x1, int y1, int x2, int y2, char *color);
void nio_draw_line_rgb(int x1, int y1, int x2, int y2, int r, int g, int b);
void nio_draw_line_rand(int x1, int y1, int x2, int y2);
void nio_draw_arc(int x, int y, int r, char *color);
void nio_draw_arc_rgb(int x, int y, int r, int red, int b, int g);
void nio_draw_arc_rand(int x, int y, int r);

// Sound functions

void nio_sound(int status);

void nio_beep(void);

void nio_load_music(char *filename);
void nio_play_music(int loops);
void nio_stop_music(void);
bool nio_music_playing(void);

int  nio_load_sound(char* filename);
void nio_play_sound(int sound_num, int loops);
void nio_free_sound(int i);

// Image functions

int  nio_load_image(char *filename);
void nio_draw_image(int x, int y, int image_num);
void nio_free_image(int i);

void nio_term_init(int font_num, int color);

/*********************/
/* NIO Rand Routines */
/*********************/

#ifndef RAND_MAX
#define RAND_MAX 32767
#endif

void randomize(void);
int  nio_rand_int(int i);
bool nio_rand_bool(void);

// Key/Button States

enum { PRESSED = 0x01, RELEASED = 0x00 };

// Sound status

enum { NIO_ON = 0x01, NIO_OFF = 0x00 };

#endif /* _NIO_LIB */

#ifdef  __cplusplus
}
#endif

