/*
 *    new_rpc.c
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
 *    Soli Deo Gloria
 *
 */

#include "../misc_lib/wlog.h"
#include "sock_lib.h"
#include "types.h"
#include "buffer.h"
#include "new_rpc.h"

#ifndef STDIN
#define STDIN     (0)
#endif

#ifndef STDOUT
#define STDOUT    (1)
#endif

/*
#ifndef STDERR
#define STDERR    (2)
#endif
*/

#define HOSTNAME_LEN    (32)
#define STR_LEN         (256)

//static SOCKET s;

static int fd_in;
static int fd_out;
//static int fd_err;

static int nrpc_server = FALSE;

void
nrpc_init_server(void)
{
/*
  char hostname[HOSTNAME_LEN];
  char welcome[BUF_SIZE];

  gethostname(hostname, HOSTNAME_LEN);

  snprintf(welcome, BUF_SIZE, "NIO Test Server 0.04 (%s)", hostname);

  wlog("nrpc_init_server(): welcome = |%s|\n", welcome);

  pack_string(welcome);

  write_buffer(STDOUT);

//  printf("%s", welcome);  // Send welcome to client.
//  fflush(stdout);

  wlog("Welcome sent...\n");
*/

  fd_in = STDIN;
  fd_out = STDOUT;

  reset_buf();

//  wlog("Buffer reset...\n");

  nrpc_server = TRUE;

//  usleep(10000);
}

int
nrpc_init_client(SOCKET s)
{
//  char str[BUF_SIZE];

//  s = call_socket(server, port_num);

//  printf("Socket initialized...\n");

  /* Get welcome message */

  fd_in = s; 
  fd_out = s;

/*
  read_buffer(s);

//  read_socket(s, str, 256);

  printf("Socket read...\n\n");

  unpack_string(str);

  printf("welcome = |%s|\n", str);
  fflush(stdout);
*/

  reset_buf();

  return(0);
}

/*
void
nrpc_welcome(char *str)
{
  int len = strlen(str);

  write_socket(s, str, len);
}
*/

void
nrpc_send_message(void)
{
//  wlog("nrpc_send_message(): calling wr_buffer()...\n");

  // Send message and get response
  wr_buffer(fd_out, fd_in);
}

void
nrpc_send_response(void)
{
  write_buffer(fd_out);
}

void
nrpc_reverse(void)
{
  write(fd_out, "reverse", 7);
}

void
nrpc_exit(void)
{
  write(fd_out, "exit", 4);
}

/*
void
nrpc_close(void)
{
  if (! nrpc_server)
    close_socket(s);
}
*/

void
nrpc_set_function(Sint16 func_num)
{
  reset_buf();
  pack_int16(func_num);
}

Sint16
nrpc_get_function(void)
{
  Sint16 func_num;

  read_buffer(fd_in);

  if (cmp_buf("exit")) {
    return(NRPC_EXIT);
  }

  if (cmp_buf("reverse")) {
    return(NRPC_REVERSE);
  }

  func_num = unpack_int16();

//  wlog("nrpc_get_function(): func_num = %d\n", func_num);

  return(func_num);
}

void
nrpc_std_response(void)
{
  reset_buf();

  pack_int8(0);

  nrpc_send_response();
}

void
nrpc_wait_for_reverse(void)
{
  for (;;)
  {
    Sint16 func_num;

    func_num = nrpc_get_function();

    if (func_num == NRPC_EXIT) {
//      wlog("Exit command rcvd.\n");
      exit(0); // This does not look right...
    }
    else if (func_num == NRPC_REVERSE) {
//      wlog("Reverse command rcvd.\n");
      break;
    }
    else {
//      wlog("bad function number!\n");
    }
  }
}

