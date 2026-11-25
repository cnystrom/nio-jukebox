/*
 * wlog.c
 *
 * write log: basic logging mechanism
 *
 * Chris Nystrom
 *
 * (c) 2004
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "uio.h"
#include "wlog.h"

static int fd;

int
wlog_open_file(char *pathname)
{
  fd = uio_open_file_wr(pathname);

  return(fd);
}

void
wlog_open_fd(int fd_in)
{
  fd = fd_in;
}

int
wlog(const char *format, ...)
{
  byte line[BUFSIZ];
  va_list ap;

  va_start(ap, format);
  vsprintf(line, format, ap);
  va_end(ap);

  return(uio_put_line(fd, line));
}

int
wlog_close(void)
{
  return(close(fd));
}

