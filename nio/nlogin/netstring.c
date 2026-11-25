//
//  netstring.c (file descriptor version)
//
//  From:
//    http://cr.yp.to/proto/netstrings.txt
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "netstring.h"

#ifndef NUL
#define NUL  (0)
#endif

int get_size(int fd);
int writef(int fd, char *format, ...);

int
encode_netstring(char *buf, int fd)
{
  int len;

  len = strlen(buf);

  if (len <= 0 || len > BUFSIZ) {
    fprintf(stderr, "encode_netstring(): length bad.\n");
    return -1;
  }

  if (writef(fd, "%u:", len) < 0) {
    fprintf(stderr, "encode_netstring(): length bad.\n");
    return -2;
  }

  if (write(fd, buf, len) < len) {
    fprintf(stderr, "encode_netstring(): write failed.\n");
    return -3;
  }

  if (write(fd, ",", 1) <= 0) {
    fprintf(stderr, "encode_netstring(): comma write failed.\n");
    return -4;
  }

  return(len);
}

int
decode_netstring(char *buf, int fd)
{
  char c;
  int len;

  len = get_size(fd);

  if (len <= 0 || len > BUFSIZ) {
    fprintf(stderr, "decode_netstring(): length bad.\n");
    return -2;
  }

  if (read(fd, buf, len) < len) {
    fprintf(stderr, "decode_netstring(): read failed.\n");
    return -4;
  }

  read(fd, &c, 1);

  if (c != ',') {
    fprintf(stderr, "decode_netstring(): missing comma.\n");
    return -5;
  }

  return(len);
}

int
get_size(int fd)
{
  char c;
  int i = 0;
  char s[BUFSIZ];

  read(fd, &c, 1);

  while (c != NUL && c != ':') {
    s[i++] = c;
    read(fd, &c, 1);
  }

  s[i] = 0;

  return(atoi(s));
}

int
writef(int fd, char *format, ...)
{
  int len, ret;
  char buf[BUFSIZ];
  va_list ap;

  va_start(ap, format);
  vsprintf(buf, format, ap);
  va_end(ap);

  len = strlen(buf);

  ret = write(fd, buf, len);

  return(ret);
}

/*
int
main(void)
{
  char s[BUFSIZ];

  encode_netstring("This is a test", STDOUT);

  printf("\nINPUT> ");
  fflush(stdout);

  // cut and paste above output into here to test
  decode_netstring(s, STDIN);

  printf("\ns = |%s|\n", s);

  exit(0);
}
*/

