/*
 * client.c
 */

#include <stdio.h>
#include "../misc_lib/wlog.h"
#include "sock_lib.h"
#include "new_rpc.h"
#include "example.h"

#ifndef STDOUT
#define STDOUT  (1)
#endif

int
main(void)
{
  SOCKET s;

  wlog_open_fd(STDOUT);

  s = call_socket("localhost", PORTNUM);

  printf("Socket initialized...\n");

  nrpc_init_client(s);

  echo_data();

  nrpc_exit();
  close_socket(s);

  wlog_close();
  exit(0);
}

