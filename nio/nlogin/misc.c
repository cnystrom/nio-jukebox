/*
    sdl_misc.c
*/

#include "SDL.h"
#include "misc.h"

void
set_window_caption(char *s)
{
  SDL_WM_SetCaption(s, s);
}

void
mouse_cursor(int i)
{
  if (ON == i)
    SDL_ShowCursor(SDL_ENABLE);
  else if (OFF == i)
    SDL_ShowCursor(SDL_DISABLE);
}

int
get_ticks(void)
{
  return(SDL_GetTicks());
}

