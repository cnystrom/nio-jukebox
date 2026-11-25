/*
 *    sock_lib.c
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

#include "sock_lib.h"

unsigned short pn;    /* port number */

SOCKET
establish_socket(unsigned short portnum)
{
  int reuse_addr = 1;
  char   myname[256];
  struct sockaddr_in sa;
  struct hostent *hp;
  SOCKET s;

  memset(&sa, 0, sizeof(struct sockaddr_in));

  gethostname(myname, sizeof(myname));

  hp = gethostbyname(myname);

  if (hp == NULL)
    return(INVALID_SOCKET);

  sa.sin_family = hp->h_addrtype;

  sa.sin_port = htons(portnum);

  s = socket(AF_INET, SOCK_STREAM, 0);

//  printf("s = %d\n", s);

  if (s == INVALID_SOCKET)
    return INVALID_SOCKET;

  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse_addr,
    sizeof(reuse_addr));

  if (bind(s, (struct sockaddr *) &sa, sizeof(struct sockaddr_in))
#ifdef WIN32
     == SOCKET_ERROR)
#else
     < 0)
#endif
  {
#ifdef WIN32
    closesocket(s);
#else
    close(s);
#endif

    return(INVALID_SOCKET);
  }

  listen(s, 3);    // max # of queued connects 
  return(s);
}

SOCKET
open_socket(unsigned short portnum)
{
  SOCKET s;

  pn = portnum;

  if ((s = establish_socket(portnum)) == INVALID_SOCKET)
  {
    perror("establish");
    exit(1);
  }

//  printf("socket established...\n");

  return(s);
}

SOCKET
accept_socket(SOCKET s)
{
  SOCKET new_sock;

//  printf("Waiting for incoming connection on port: %d...\n", pn);

  new_sock = accept(s, NULL, NULL);

//  printf("new_sock = %d\n", new_sock);

  if (s == INVALID_SOCKET) 
  {
    fprintf(stderr, "Error waiting for new connection!\n");
    return(INVALID_SOCKET);
  }

//  printf("Connection success!\n");

  return(new_sock);
}

void
close_socket(SOCKET s)
{
#ifdef WIN32
  closesocket(s);
#else
  close(s);
#endif
}

void
puts_socket(SOCKET s, char *str)
{
  int i;

  i = strlen(str);

  printf("OUT> %s\n", str);

  if (send(s, str, i, 0) == -1)
    perror("send");
}

u_int
gets_socket(SOCKET s, char *str, u_int max_len)
{
  int i;

  if ((i = recv(s, str, max_len - 1, 0)) == -1)
    perror("recv");

  str[i] = '\0';

//  printf("IN> %s\n", str);

  return(strlen(str));
}

SOCKET
call_socket(const char *hostname, unsigned short portnum)
{
  struct sockaddr_in sa;
  struct hostent     *hp;
  SOCKET s;

  hp = gethostbyname(hostname);

  if (hp == NULL)
    return INVALID_SOCKET;

  memset(&sa, 0, sizeof(sa));

  memcpy((char *) &sa.sin_addr, hp->h_addr, hp->h_length);

  sa.sin_family = hp->h_addrtype;
  sa.sin_port = htons((u_short) portnum);

  s = socket(hp->h_addrtype, SOCK_STREAM, 0);

  if (s == INVALID_SOCKET)
    return INVALID_SOCKET;

  if (connect(s, (struct sockaddr *) &sa, sizeof sa)
#ifdef WIN32
     == SOCKET_ERROR)
#else
     < 0)
#endif
  {
    close_socket(s);
    return INVALID_SOCKET;
  }

  return s;
}

int
read_socket(SOCKET s, char *buf, int n)
{
  return(read(s, buf, n));
}

int
read_socket_n(SOCKET s, char *buf, int n)
{
  int bcount; /* counts bytes read */
  int br;     /* bytes read this pass */

  bcount= 0;
  br= 0;

  while (bcount < n)
  {             // loop until full buffer 
    printf("bcount = %d\n", bcount);
    if ((br = read(s, buf, n-bcount)) > 0)
    {
      bcount += br;                // increment byte counter 
      buf += br;                   // move buffer ptr for next read 
    }
    else if (br < 0)               // signal an error to the caller 
      return(-1);
  }

  return(bcount);
}

int
write_socket(SOCKET s, char *buf, int n)
{
  int nleft, nwritten;

  nleft = n;

  while (nleft > 0) {
    nwritten = write(s, buf, nleft);

    if (nwritten <= 0)
      return(nwritten);  // error 

    nleft -= nwritten;
    buf   += nwritten;
  }

  return(n - nleft);
}

