/*
 *    list.c
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
 *    E-Mail: ccn@olenska.hn.org, nystrom@cactus.org,
 *              or cnystrom@talmid.sps.mot.com
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../misc_lib/wlog.h"
#include "../new_rpc/buffer.h"
#include "netstring.h"

#define HOSTNAME_LEN  (256)

// int getline(char *line, int max);

int
main(int argc, char *argv[])
{
  char hostname[HOSTNAME_LEN];
  char s[BUF_SIZE];

  wlog_open_file("/var/tmp/niod.log");

  gethostname(hostname, HOSTNAME_LEN);

  snprintf(s, BUF_SIZE, "NIO Test Server 0.04 (%s)", hostname);

  wlog("nrpc_init_server(): welcome = |%s|\n", s);

  usleep(10000);

  encode_netstring(s, stdout);
  fflush(stdout);

//  printf("%s", s);  // Send welcome to client.
//  fflush(stdout);

  wlog("Welcome sent...\n");

  if (decode_netstring(s, stdin) > 0) {
    wlog("command = |%s|\n", s);
    system(s);
    wlog("back from system() call...\n");
  }
 
  wlog_close();
  exit(0);
}

/*
int
getline(char *line, int max)
{
  if (fgets(line, max, stdin) == NULL)
    return 0;
  else
    return strlen(line);
}
*/

