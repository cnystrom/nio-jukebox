
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "SDL.h"
#include "../new_rpc/new_rpc.h"
#include "nio_sdl.h"
#include "misc.h"
#include "colors.h"
#include "fonts.h"
#include "text.h"
#include "sound.h"
#include "screen.h"
#include "home_dir.h"
#include "keyboard.h"
#include "text_box.h"
#include "rpc.h"
#include "url.h"
#include "file_xfr.h"
#include "netstring.h"

#define MAX_URL_LEN     64

#define LOG_PATH        "./.nio/logs/"

void nio_client_main_loop(void);
int  get_string(char *s1, char *s2);
int  get_passwd(char *s1, char *s2);
void exit_main(void);
void randomize(void);

int
main(void)
{
  int fw;  // font width
  int sound_0;
  int font_0;
  int font_1; 
  Uint32 fg, bg;
//  char s[MAX_URL_LEN + 1] = "nio://olenska.newio.org/list.nio";
  char s[MAX_URL_LEN + 1] = "nio://shuttle.newio.org/list.nio";
//  char s[MAX_URL_LEN + 1] = "nio://localhost/list.nio";
  char server[MAX_LINE_LEN];
  char program[MAX_LINE_LEN];
  char username[MAX_LINE_LEN] = "";
  char password[MAX_LINE_LEN] = "";
  char command[MAX_LINE_LEN * 3];
  url url;
  glyphFont gf0, gf1;
  SDL_Rect r;

//  wlog_init_file("nlogin.log");

  randomize();

  check_home_dir();

  sdl_init();
  init_audio();

  sound_0 =load_sound("/usr/share/nlogin/newio.wav");
  play_sound(sound_0, 0);
  delete_sound(sound_0);

  for (;;)
  {
    init_screen(640, 32, SDL_ANYFORMAT);

    set_window_caption("Welcome to nlogin application browser");

    fg = get_color("white");
    bg = get_color("black");

    font_0 = load_sys_font(NIO_DEFAULT_FONT,
                 NIO_DEFAULT_PTSIZE,
                 NIO_STYLE_NORMAL,
                 fg, bg);

    font_1 = load_sys_font(NIO_DEFAULT_FONT,
                 NIO_DEFAULT_PTSIZE,
                 NIO_STYLE_NORMAL,
                 bg, fg);

    gf0 = get_font(font_0);
    gf1 = get_font(font_1);

    text_size(&gf0, "X", &r);

//    fw = gf0.width;
    fw = r.w; // font width

    draw_text(&gf0, "URL:", fw * 3, 6);

    text_box(s, 64, fw * 8, 6, font_1, fg, bg, FALSE);

    parse_url(&url, s);

//    print_url(&url);

    if (! strncmp(url.service, "http", 4))
    {
      char s2[512] = "mozilla ";

      free_font(font_0);
      free_font(font_1);

      strcat(s2, s);
      system(s2);
    }
    else if (! strncmp(url.service, "nio", 4))
    {
      char str[BUFSIZ];
      SOCKET s;

      init_screen(640, 64, SDL_ANYFORMAT);

      draw_text(&gf0, "Login:", fw * 3, 6);
      draw_text(&gf0, "Password:", fw * 3, 32);

      text_box(username, 16, fw * 12, 6, font_1, fg, bg, FALSE);
      text_box(password, 16, fw * 12, 32, font_1, fg, bg, TRUE);

      free_font(font_0);
      free_font(font_1);

      set_login(username);
      set_password(password);

      init_screen(640, 480, SDL_ANYFORMAT);

      set_window_caption(url.program);

      strcpy(server, url.server);
      strcpy(program, url.program);

      strcpy(command, "/home/cnystrom/nio/");
      strcat(command, program);
      strcat(command, ".nio");

//      printf("server   = %s\n", server);
//      printf("username = %s\n", username);
//      printf("password = %s\n", password);
      printf("command  = %s\n", command);

//      printf("calling application ...\n");

//      nrpc_init_client(username, server, command, password);

      s = call_socket(server, 32662);

      decode_netstring(str, s);

      printf("welcome = |%s|\n", str);

      encode_netstring(command, s);

      printf("command |%s| sent...\n", command);

      nrpc_init_client(s);

//      printf("application called...\n");

//      sleep(3);

//     printf("done sleeping....\n");

      nio_client_main_loop();

      close_socket(s);

    }
  }

  SDL_Quit();
//  wlog_close();
  exit(0);
}

/* Seed the randomizer with the timer */
void
randomize(void)
{
  time_t timer;
  srand ((unsigned) time (&timer));
}

