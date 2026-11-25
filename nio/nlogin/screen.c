/*
    screen.c

*/

#include <SDL.h>
#include "ascii_key.h"
#include "colors.h"
#include "SDL_prim.h"
#include "images.h"
#include "screen.h"

static SDL_Surface *screen = NULL;

int
init_screen(int sw, int sh, int options)
{
  screen = SDL_SetVideoMode(sw, sh, 0, options);

  if ( screen == NULL ) {
    fprintf(stderr, "Can not set video mode: %s\n", SDL_GetError());
    return(-1);
  }

  return(0);
}

SDL_PixelFormat *
get_pixel_format(void)
{
  return(screen->format);
}

void
blit_screen(SDL_Surface *s, SDL_Rect *r)
{
  SDL_BlitSurface(s, NULL, screen, r);
}

void
fill_rect(SDL_Rect *r, Uint32 color)
{
  SDL_FillRect(screen, r, color);
}

void
clear_screen(Uint32 color)
{
//  printf("clear_screen(): color = %d\n", color);

  SDL_FillRect(screen, NULL, color);
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void
update_screen(void)
{
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void
update_rectangle(int x, int y, int w, int h)
{
//  printf("x = %d\n", x);
//  printf("y = %d\n", y);
//  printf("w = %d\n", w);
//  printf("h = %d\n", h);

  SDL_UpdateRect(screen, x, y, w, h);
}

void
lockScreen(void)
{
  if ( SDL_MUSTLOCK(screen) ) {
    if ( SDL_LockSurface(screen) < 0 ) {
      fprintf(stderr, "Can't lock screen: %s\n", SDL_GetError());
      return;
    }
  }
}

void
unlockScreen(void)
{
  if ( SDL_MUSTLOCK(screen) ) {
    SDL_UnlockSurface(screen);
  }
}

int
get_screen_width(void)
{
  if (screen == NULL)
  {
    fprintf(stderr, "get_screen_width(): screen not set.\n");
    return(1);
  }

  return(screen->w);
}

int
get_screen_height(void)
{
  if (screen == NULL)
  {
    fprintf(stderr, "get_screen_height(): screen not set.\n");
    return(-1);
  }

  return(screen->h);
}

//============================================================

int
draw_rectangle(int x, int y, int w, int h, Uint32 color)
{
  SDL_Rect dstrect;

//  printf("x = %d\n", x);
//  printf("y = %d\n", y);
//  printf("w = %d\n", w);
//  printf("h = %d\n", h);

  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = w;
  dstrect.h = h;

  SDL_FillRect(screen, &dstrect, color);

  SDL_UpdateRects(screen, 1, &dstrect);

  return(0);
}

void
draw_line(int x1, int y1, int x2, int y2, Uint32 color)
{
//	printf("Drawing line from %d, %d to %d, %d\n", x1, y1, x2, y2);

  lockScreen();
  SDL_drawLine_TG(screen, x1, y1, x2, y2, color, 0, 0);
  unlockScreen();

  SDL_UpdateRects(screen, 1, &screen->clip_rect);
}

void
draw_arc(int x, int y, int r, Uint32 color)
{
  lockScreen();
  SDL_drawCircle_TG(screen, x, y, r, color, 0, 0);
  unlockScreen();

  SDL_UpdateRects(screen, 1, &screen->clip_rect);
}

int
draw_image(int i_num, int x, int y)
{
  SDL_Surface *image;
  SDL_Rect dstrect;

  if (i_num < 0) {
    fprintf(stderr, "draw_image(): no image available to draw.\n");
    return(-1);
  }

  image = get_image(i_num);

  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = image->w;
  dstrect.h = image->h;

  if (SDL_BlitSurface(image, NULL, screen, &dstrect) == 0) {
    SDL_UpdateRects(screen, 1, &dstrect);
    return(0);
  }
  else {
    fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
    return(-1);
  }
}

void
draw_point(int x, int y, Uint32 color)
{
  lockScreen();
  putpixel(x, y, color);
  unlockScreen();

  SDL_UpdateRect(screen, x, y, 1, 1);
}

//
//  Return the pixel value at (x, y)
//
//  NOTE: The surface must be locked before calling this!
//
Uint32
getpixel(int x, int y)
{
  int bpp = screen->format->BytesPerPixel;

  // Here p is the address to the pixel we want to retrieve 

  Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;

    case 2:
      return *(Uint16 *)p;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
      return *(Uint32 *)p;

    default:
      return 0;       // shouldn't happen, but avoids warnings 
    }
}

//
// Set the pixel at (x, y) to the given value
//
//   NOTE: The surface must be locked before calling this!
//
void
putpixel(int x, int y, Uint32 pixel)
{
  int bpp = screen->format->BytesPerPixel;

  // Here p is the address to the pixel we want to set

  Uint8 *p = (Uint8 *) screen->pixels + y * screen->pitch + x * bpp;

  switch(bpp) {
    case 1:
      *p = pixel;
      break;

    case 2:
      *(Uint16 *)p = pixel;
      break;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
      
    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

