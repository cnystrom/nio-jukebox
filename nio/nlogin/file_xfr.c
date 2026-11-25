/*
 *    file_xfr.c
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
 *              or cnystrom@gmail.com
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../scp_lib/scp_lib.h"
#include "bool.h"
#include "misc_io.h"
#include "file_xfr.h"

int copy_file(char *filename, char *filepath);

static char server[256];
static char app_name[256];
static char app_ver[256];
static char cwd[256];

static char login_name[16];
static char password[16];

static char niodir[256];   // NIO cache dir

static char dirname[256];  // Where the application files will be moved to

static char filepath[256]; // where file can be found

void
init_file_loader(char *s, char *an, char *av, char *dir)
{
  strcpy(server, s);
  strcpy(app_name, an);
  strcpy(app_ver, av);
  strcpy(cwd, dir);

//  printf("init_file_loader(): cwd = %s\n", cwd);

  get_homedir(niodir);
  strncat(niodir, "/.nio/cache/", 12);
  strcpy(dirname, niodir);
  check_dir(dirname);

  strcat(dirname, server);
  strcat(dirname, "/");
  check_dir(dirname);
   
  strcat(dirname, app_name);
  strcat(dirname, "/");
  check_dir(dirname);

  strcat(dirname, app_ver);
  strcat(dirname, "/");
  check_dir(dirname);

//  printf("init_file_loader(): dirname = %s\n", dirname);
}

void
set_login(char *ln)
{
  strcpy(login_name, ln);
}

void
set_password(char *pw)
{
  strcpy(password, pw);
}

char *
load_file(char *filename)
{
//  printf("load_file(): filename = %s\n", filename);

  strcpy(filepath, dirname);
  strcat(filepath, basename(filename));

//  printf("load_file(): filepath = %s\n", filepath);

  if (! file_exists(filepath)) {
    printf("File %s does not exist in cache.\n", basename(filename));
    printf("Copying from server...\n");
    copy_file(filename, filepath);
  }

  return(filepath);
}

int
copy_file(char *filename, char *filepath)
{
  char command[256];

  strcpy(command, login_name);
  strcat(command, "@");
  strcat(command, server);
  strcat(command, ":");
//  strcat(command, cwd); 
  strcat(command, "nio/");
  strcat(command, filename);

//  printf("copy_file(): command = %s\n", command);
//  printf("copy_file(): filepath = %s\n", filepath);
//  printf("copy_file(): login_name = %s\n", login_name);
//  printf("copy_file(): password = %s\n", password);

  scp_file(command, filepath, password);
//  sleep(1);

  if (! file_exists(filepath)) {
    fprintf(stderr, "copy_file(): Failed. Retrying...\n");
    scp_file(command, filepath, password);
    sleep(1);
  }

  if (! file_exists(filepath)) {
    fprintf(stderr, "copy_file(): Failed. Retrying again...\n");
    scp_file(command, filepath, password);
    sleep(2);
  }

  if (! file_exists(filepath)) {
    fprintf(stderr, "copy_file(): Failed.\n");
    return(-1);
  }

  return 0;
}

/*
char *
get_file_path(int index)
{
  if (index >= 0 && index < file_index)
  {
    printf("index = %d\n", index);
    printf("file_list[index] = ");
    printf(file_list[index]);
    printf("\n");

    return(file_list[index]);
  }
  else
  {
    printf("get_file_path: bad index value %d\n", index);
    return(NULL);
  }
}
*/

