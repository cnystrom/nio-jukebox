
#ifndef _NIO_SDL_MOUSE
#define _NIO_SDL_MOUSE

typedef struct {
  int x;
  int y;
} point_t;

/*
typedef struct {
  int b1;
  int b2;
  int b3;
  int x;
  int y;
} mouse_state;
*/

enum { PRESSED = 0x01, RELEASED = 0x00 };

point_t mouse_get_xy(void);
void    mouse_set_xy(point_t p);

void    mouse_button_handler(Uint8 type, Uint8 button);

int     mouse_button_get(int i);

#endif /* _NIO_SDL_MOUSE */
 
