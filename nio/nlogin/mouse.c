
#include <stdio.h>
#include "SDL.h"
#include "mouse.h"

static int mouse_x = 0;
static int mouse_y = 0;

static int mouse_left;
static int mouse_middle;
static int mouse_right;

void
mouse_button_handler(Uint8 type, Uint8 button)
{
  switch(button) {
    case SDL_BUTTON_LEFT:
      if (type == SDL_MOUSEBUTTONDOWN) {
        mouse_left = PRESSED;
      } else {
        mouse_left = RELEASED;
      }
      break;

    case SDL_BUTTON_MIDDLE:
      if (type == SDL_MOUSEBUTTONDOWN) {
        mouse_middle = PRESSED;
      } else {
        mouse_middle = RELEASED;
      }
      break;

    case SDL_BUTTON_RIGHT:
      if (type == SDL_MOUSEBUTTONDOWN) {
        mouse_right = PRESSED;
      } else {
        mouse_right = RELEASED;
      }
  }
}

int
mouse_button_get(int i)
{
  if (i == 1) {
    return(mouse_left);
  }

  if (i == 2)
    return(mouse_middle);

  if (i == 3) {
    return(mouse_right);
  }

  fprintf(stderr, "nlogin: bad value passed to mouse_button_get(): %d\n", i);

  return(0);
}

point_t
mouse_get_xy(void)
{
  point_t p;

  p.x = mouse_x;
  p.y = mouse_y;

  return(p);
}

void
mouse_set_xy(point_t p)
{
  mouse_x = p.x;
  mouse_y = p.y;
}

