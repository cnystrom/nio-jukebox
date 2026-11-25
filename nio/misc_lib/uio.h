/*
 * uio.h
 *
 */

#ifndef UIO
#define UIO

typedef char byte;

#ifndef EOF
#define EOF       (-1)
#endif

#ifndef BUFSIZ
#define BUFSIZ    (8192)
#endif

#define STDIN     (0)
#define STDOUT    (1)
#define STDERR    (2)

//int vsprintf(char *str, const char *format, va_list ap);

int  uio_open_file_rd(char *pathname);
int  uio_open_file_wr(char *pathname);
int  uio_open_file_rw(char *pathname);

int  uio_write_byte(int fd, byte b);
byte uio_read_byte(int fd);

int  uio_get_line(int fd, byte *line, int lim);
int  uio_put_line(int fd, byte *line);
int  uio_put_linef(int fd, char *format, ...);

#endif /* UIO */

