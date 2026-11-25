/*
 *    misc_io.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "bool.h"
#include "ascii_key.h"
#include "misc_io.h"

int
get_homedir(char *s)
{
  int len;
  char *tmp;

  if ((tmp = getenv("HOME")) == NULL)
  {
    fprintf(stderr, "Everyone needs a HOME.\n");
    exit(1);
  }

  len = strlen(tmp);

  strncpy(s, tmp, len);

  s[len] = NUL;
 
//  printf("s = %s\n", s);

  return(len);
}

bool
directory_exists(char *s)
{
  struct stat buf;

#ifdef UNIX
  if (lstat(s, &buf) < 0)
#else
  if (stat(s, &buf) < 0)
#endif
  {
    return(FALSE);
  }  

  if (S_ISDIR(buf.st_mode))
    return(TRUE);
  else
    return(FALSE);
}

bool
file_exists(char *s)
{
  struct stat buf;

#ifdef UNIX
  if (lstat(s, &buf) < 0)
#else
  if (stat(s, &buf) < 0)
#endif
  {
    return(FALSE);
  }  

  if (S_ISREG(buf.st_mode))
    return(TRUE);
  else
    return(FALSE);
}

void
check_dir(char *s)
{
  if ( ! directory_exists(s))
  {
#ifdef UNIX
    if (mkdir(s, 0755) != 0)
#else
    if (mkdir(s) != 0)
#endif
    { 
      printf("check_dir: mkdir failed for %s\n", s);
    }
  }
}

char *
basename(char *s)
{
  char *s2 = s;
   
  while (*s)
  {
#ifdef UNIX
    if (*s++ == '/')
#else
    if (*s++ == '\\')
#endif
      s2 = s;
  }

  return(s2);
}

