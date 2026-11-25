/*
 * server.c
 */

#include <stdio.h>
#include "../misc_lib/wlog.h"
#include "new_rpc.h"
#include "example.h"

#define STR_LEN		(128)

int
main(void)
{
  char str[] = "This is a test of a very long string!\n";

  wlog_open_file("/var/tmp/server.log");

  wlog("Logfile opened...\n");

  nrpc_init_server();

  wlog("Server initialized...\n");

  wlog("INT_MAX = %d\n", INT_MAX);
  test_send_int(INT_MAX);

  wlog("INT_MIN = %d\n", INT_MIN);
  test_send_int(INT_MIN);

  wlog("Sending string |%s|...\n", str);
  test_send_string(str);

  wlog("Testing combo...\n");
  test_combo(3, "The is a test string.\n");

/*
  wlog("--\nSENDING REVERSE\n--\n");

  nrpc_reverse();
  echo_data();
*/

  nrpc_exit();
  wlog_close();
  exit(0);
}

