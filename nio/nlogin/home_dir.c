/*
 *    home_dir.c
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

#include <string.h>
#include "bool.h"
#include "misc_io.h"
#include "home_dir.h"

void
check_home_dir(void)
{
  int home_dir_len;
  char nio_dir[256];
  char cache_dir[256];
  char log_dir[256];

  home_dir_len = get_homedir(nio_dir);
//  printf("nio_dir = %s\n", nio_dir);

  strncat(nio_dir, "/.nio/", 6);
//  printf("nio_dir = %s\n", nio_dir);
  check_dir(nio_dir);

  strncpy(cache_dir, nio_dir, home_dir_len + 6);
  strncat(cache_dir, "cache/", 6);
//  printf("cache_dir = %s\n", cache_dir);
  check_dir(cache_dir);

  strncpy(log_dir, nio_dir, home_dir_len + 6);
  strncat(log_dir, "logs/", 11);
//  printf("log_dir = %s\n", log_dir);
  check_dir(log_dir);
}

