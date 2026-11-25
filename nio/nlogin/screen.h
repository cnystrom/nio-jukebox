/*
    screen.h
*/

#ifndef _NIO_SCREEN_H
#define _NIO_SCREEN_H

int init_screen(int sw, int sh, int options);
SDL_PixelFormat * get_pixel_format(void);

void blit_screen(SDL_Surface *s, SDL_Rect *r);
void fill_rect(SDL_Rect *r, Uint32 color);
void clear_screen(Uint32 color);
void update_screen(void);
void update_rectangle(int x, int y, int w, int h);
void reset_screen(void);
int get_screen_width(void);
int get_screen_height(void);

//int  set_palette(void);

int  clear_rectangle(int x, int y, int w, int h, Uint32 color);
int  draw_rectangle(int x, int y, int w, int h, Uint32 color);
void draw_line(int x1, int y1, int x2, int y2, Uint32 color);
void draw_arc(int x, int y, int r, Uint32 color);

int  draw_image(int i_num, int x, int y);
//int  display_text_on_screen(int x, int y);
//void draw_text(char *s, int x, int y);
//void draw_char(int c, int x, int y);
void draw_point(int x, int y, Uint32 color);
Uint32 getpixel(int x, int y);
void putpixel(int x, int y, Uint32 pixel);

#endif /* _NIO_SCREEN_H */

