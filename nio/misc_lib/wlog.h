/*
 * wlog.h
 *
 * write log: basic logging mechanism
 *
 * Chris Nystrom
 *
 * (c) 2004
 *
 */

int  wlog_open_file(char *pathname);
void wlog_open_fd(int fd_in);
int  wlog(const char *format, ...);
int  wlog_close(void);

