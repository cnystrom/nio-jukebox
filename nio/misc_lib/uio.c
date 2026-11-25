/*
 * uio.c
 *
 * unbuffered I/O functions
 *
 * Chris Nystrom
 *
 * (c) 2004
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "uio.h"

int
uio_open_file_rd(char *pathname)
{
  int fd = open(pathname, O_RDONLY);

  return(fd);
}

int
uio_open_file_wr(char *pathname)
{
  int fd = open(pathname, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

  return(fd);
}

int
uio_open_file_rw(char *pathname)
{
  int fd = open(pathname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

  return(fd);
}

int
uio_write_byte(int fd, byte b)
{
  int n = 0;

  while (n == 0) {
    n = write(fd, &b, 1);
  }

  // n < 0 -> error

  return(n);
}

byte
uio_read_byte(int fd)
{
  byte b;
  int n;

  n = read(fd, &b, 1);

  if (n < 0) {  // Error condition
    return n;
  }

  if (n == 0) {  // nothing left to give
    return(EOF);
  }

  return b;
}

int
uio_get_line(int fd, byte *line, int lim) 
{
  byte b;
  int  i = 0;

  while (i < (lim - 1)) {

    b = uio_read_byte(fd);

    if (b == EOF || b <= 0) {
      break;
    }

    if (b != 13) {      // char 13 not needed in unix
      *(line + i) = b;
      i++;
    }
 
    if (b == '\n') {
      break;  
    }
  }

  *(line + i) = '\0';

  return i;
}

int
uio_put_line(int fd, byte *line)
{
  int i, len, ret = 0;

  len = strlen(line);

  for (i = 0; i < len; i++) {
    ret = uio_write_byte(fd, *(line + i));

    if (ret <= 0) {
      break;
    }
  }

  return (i);
}

int
uio_put_linef(int fd, char *format, ...)
{
  int ret;
  byte l[BUFSIZ];
  va_list ap;

  va_start(ap, format);
  vsprintf(l, format, ap);
  va_end(ap);

  ret = uio_put_line(fd, l);

  return(ret);
}

/*
int
main(void)
{
  byte l[BUFSIZ];

//  int log_fd = uio_open_file_wr("uio.log");

  while (1) {
    uio_get_line(STDIN, l, BUFSIZ);

    if (strncmp(l, "exit", 4) == 0) {
      break;
    }

    uio_put_line(STDOUT, l);
  }

//  close(log_fd);
}
*/

