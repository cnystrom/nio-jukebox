
#include "SDL.h"
#include "nio_sdl.h"
#include "ascii_key.h"
#include "keyboard.h"

int  get_kval(void);
void put_kval(int i);

static int kval;

int
get_kval(void)
{
  return(kval);
}

void
put_kval(int i)
{
  kval = i;
}

void
PrintKeyInfo( SDL_KeyboardEvent *key )
{
  if( key->type == SDL_KEYUP )
  {
    kval = NUL;
  }
  else
  {
    if ((key->keysym.unicode & 0xFF80) == 0)
    {
      kval = key->keysym.unicode & 0x7F;
//      printf("\nkval = %d\n", kval);
//      fflush(stdout);
    }
  }
}

int
get_char(void)
{
  int c = NUL;

  put_kval(NUL);

  while (c == NUL)
  {
    int i;

    sdl_handle_event();

    i = get_kval();

    if (i >= 32 && i < 127)
      c = i;
    else if (i == SDLK_RETURN)
      c = LF;
    else if (i == SDLK_ESCAPE)
      c = ESC;
    else if (i == SDLK_BACKSPACE)
      c = BS;
    else
      c = NUL;
  }

  return(c);
}

