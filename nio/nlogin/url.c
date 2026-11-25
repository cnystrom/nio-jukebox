/*
 * url.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ascii_key.h"
#include "url.h"

void
parse_url(url *url, char *s)
{
  int check_for_port = 0;
  int check_for_extension = 0;
  int check_for_username = 0;
  int i, j, index;

//  printf("\ns = %s\n--\n", s);

  index = 0;

  for (i = 0; i < MAX_SERVICE_LEN; i++)
  {
    if (s[index] == ':')
      break;
    else
    {
      url->service[i] = s[index];
      index++;
    }
  }

  url->service[i] = NUL;

//  printf("service = %s\n", url->service);

  index++; // :
  index++; // /
  index++; // /

  j = index;

  for (i = 0; i < MAX_USERNAME_LEN; i++)
  {
    if (s[j] == '@')
    {
      check_for_username = 1;
      index = j;
      break;
    }
    else
    {
      url->username[i] = s[j];
      j++;
    }
  }

  if (check_for_username)
  {
    url->username[i++] = NUL;
    index++; // @
  }
  else
  {
    url->username[0] = NUL;
  }

  for (i = 0; i < MAX_SERVER_LEN; i++)
  {
    if (s[index] == ':')
    {
      check_for_port = 1;
      break;
    }
    else if (s[index] == '/')
      break;
    else if (s[index] == NUL)
    {
      url->server[i] = NUL;
      return;
    }
    else
    {
      url->server[i] = s[index];
      index++;
    }
  }

  url->server[i++] = NUL;

//  printf("server = %s\n", url->server);

  index++; // ; or /

  if (check_for_port)
  {
    for (i = 0; i < MAX_PORT_LEN; i++)
    {
      if (s[index] == '/')
        break;
      else if (s[index] == NUL)
      {
        url->port[i] = NUL;
        return;
      }
      else
      {
        url->port[i] = s[index];
        index++;
      }
    }
    url->port[i] = NUL;
    index++; // /
  }
  else
  {
    strncpy(url->port, "0", 1);
  }

//  printf("port = %s\n", url->port);

  for (i = 0; i < MAX_LINE_LEN; i++)
  {
    if (s[index] == '/')
      break;
    if (s[index] == '.')
    {
      check_for_extension = 1;
      break;
    }
    if (s[index] == NUL)
    {
      url->program[i] = NUL;
      return;
    }
    else
    {
      url->program[i] = s[index];
      index++;
    }
  }

  url->program[i] = NUL;

//  printf("program = %s\n", url->program);

  index++; // .

  for (i = 0; i < MAX_EXT_LEN; i++)
  {
    if (s[index] == NUL)
    {
      url->extension[i] = NUL;
      return;
    }
    else
    {
      url->extension[i] = s[index];
      index++;
    }
  }

  url->extension[i++] = NUL;

//  printf("extensin = %s\n", url->extension);

}

void
print_url(url *url)
{
  printf("--\n");
  printf("service   = %s\n", url->service);
  printf("username  = %s\n", url->username);
  printf("server    = %s\n", url->server);
  printf("port      = %s\n", url->port);
  printf("program   = %s\n", url->program);
  printf("extension = %s\n\n", url->extension);
}

