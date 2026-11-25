//
//   ssh_lib.c
//
//   12/03/04 - Chris Nystrom <cnystrom@gmail.com>
//


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include <pty.h>     // Linux
//#include <util.h>    // OS X
#include <sys/ioctl.h>
#include "../misc_lib/uio.h"
//#include "wlog.h"
#include "scp_lib.h"

#ifndef NEWLINE
#define NEWLINE  (10);
#endif

int  get_scp_master(void);
void get_scp_slave(void);
void set_scp_tty(void);
void scp_fail(void);
int  passwd_prompt(char *s);

int scp_master;
int scp_slave;
int scp_child;

struct termios scp_tt;

char progname[BUFSIZ];

int
scp_file(char *from_file, char *to_file, char *passwd)
{
  int ret;

//  printf("scp_file(): from_file = |%s|\n", from_file);
//  printf("scp_file(): to_file = |%s|\n", to_file);
//  printf("scp_file(): passwd = |%s|\n", passwd);

  ret = call_scp(from_file, to_file);

//  printf("scp_file(): call_scp() ret = %d\n", ret);

  if (ret < 0) {
    printf("scp call failed\n");
    return (-1);
  }

  ret = verify_scp_passwd(passwd);

//  printf("scp_file(): verify_scp_passwd() ret = %d\n", ret);

  if (ret < 0) {
    printf("login or password bad.\n");
    return (-2);
  }

  display_scp();

  return (0);
}

int
call_scp(char *from_file, char *to_file)
{
  get_scp_master();
  set_scp_tty();
  scp_child = fork();

  if (scp_child < 0) {
    perror("fork");
    scp_fail();
  }

  if (scp_child == 0) {
    get_scp_slave();
    close(scp_master);
    dup2(scp_slave, STDIN_FILENO);
    dup2(scp_slave, STDOUT_FILENO);
    dup2(scp_slave, STDERR_FILENO);
    close(scp_slave);
    execl("/usr/bin/scp", "/usr/bin/scp", "-q", from_file, to_file, 0);
    perror("execl failed");
    scp_fail();
    return 0;
  }

  close(scp_slave);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &scp_tt);
  return(scp_master);
}

int
get_scp_master(void)
{
  int ret;
  struct winsize win;

  tcgetattr(STDIN_FILENO, &scp_tt);
  ioctl(STDIN_FILENO, TIOCGWINSZ, (char *) &win);

  ret = openpty(&scp_master, &scp_slave, NULL, &scp_tt, &win);

  if (ret < 0) {
    fprintf(stderr, "openpty failed\n");
//    wlog("openpty failed\n");
    scp_fail();
  }

  return(ret);
}

void
get_scp_slave(void)
{
  setsid();
  ioctl(scp_slave, TIOCSCTTY, 0);
}

void
set_scp_tty(void)
{
  struct termios rtt;

  rtt = scp_tt;
  cfmakeraw(&rtt);
  rtt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &rtt);
}

void
scp_fail(void)
{
  kill(0, SIGTERM);
  done_scp();
}

void
done_scp(void)
{
  if (scp_child) {
    close(scp_master);
  } else {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &scp_tt);
  }
}

int
read_scp(byte *buf, int count, int uio)
{
  int ret;

//  wlog("--\nentering read_scp()...\n");

  if (uio) {
//    wlog("using uio.\n");
    ret = uio_get_line(scp_master, buf, count);
  }
  else {
//    wlog("not using uio.\n");
    ret = read(scp_master, buf, count);
  }

  if (ret < 0) {
    *buf = '\0';
  }
  else {
    *(buf + ret) = '\0';
  }

//  wlog("read_scp(): buf = |%s|\n\n", buf);

//  wlog("read_scp(): ret = %d\n", ret);
//  wlog("exiting read_scp()...\n\n");

  return(ret);
}

int
write_scp(byte *ibuf)
{
  int i;
  int count;
  int ret;
  byte tempBuf[BUFSIZ];

//  wlog("write_scp(): ibuf = |%s|\n", (char *) ibuf);

  count = strlen(ibuf);

  if (count > (BUFSIZ - 1)) {
    count = (BUFSIZ - 1);
//    wlog("count adjusted.\n");
  }

//  wlog("--\nwrite_scp(): count = %d\n", count);

  for (i = 0; i < count; i++) {
    tempBuf[i] = *(ibuf + i);
  }

  tempBuf[i++] = NEWLINE;
  count++;

  tempBuf[i] = 0;

//  wlog("write_scp(): tempBuf = |%s|\n", tempBuf);

  ret = uio_put_line(scp_master, tempBuf);

//  ret = write(scp_master, tempBuf, (count + 2));

//  wlog("count = %d\n", count);
//  wlog("ret   = %d\n", ret);

  if (ret != count) {
//    wlog("write_scp(): write error.\n");
//    wlog("(count + 2) = %d\n", (count + 2));
//    wlog("ret = %d\n", ret);
    fprintf(stderr, "write_scp(): write error.\n");
    fprintf(stderr, "write_scp(): count = %d.\n", count);
    fprintf(stderr, "write_scp(): ret = %d.\n", ret);
    fprintf(stderr, "write_scp(): ibuf = |%s|.\n", ibuf);
    fprintf(stderr, "write_scp(): tempBuf = |%s|.\n", tempBuf);
  }

//  wlog("--\n");

  return(ret);
}

void
display_scp(void)
{
  int cc;        // char count
  int flag = 1;  // flag for login check
  int ret;
  char buf[BUFSIZ];

  cc = read_scp(buf, BUFSIZ, USE_UIO);

  while(cc > 0) {

    if (flag) {
      ret = check_scp_login(buf);

      if (ret == LOGIN_BAD) {
        printf("error(): login bad.\n");
        done_scp();
        return;
      }
      else if (ret == NO_PROG) {
        printf("error(): program missing.\n");
        done_scp();
        return;
      }
      else {
        flag = 0;
      }
    }

    printf(buf);
    cc = read_scp(buf, BUFSIZ, USE_UIO);
  }

  done_scp();
}

int
verify_scp_passwd(char *passwd)
{
  int cc;  // char count
  char buf[BUFSIZ];

//  wlog("passwd = %s\n", passwd);

  cc = read_scp(buf, BUFSIZ, USE_READ);

//  wlog("ssh cc # = %d\n", cc);

  while (cc > 0) {

    buf[cc] = 0;

//    wlog("buf = |%s|\n", buf);

    if (scp_passwd_prompt(buf)) {
//      wlog("password prompt recieved.\n");
      write_scp(passwd);
//      wlog("password sent.\n");
      return 0;
    }

    cc = read_scp(buf, BUFSIZ, USE_READ);
  }

//  wlog("password verification failed\n");
  done_scp();
  return (-1);
}

int
scp_passwd_prompt(char *s)
{
  int len;
 
  len = strlen(s);
//  wlog("len = %d\n", len);
 
  if (len <= 9) {
//    wlog("-= no password match =- 1\n");
    return 0;
  }

  if (strncmp(s + len - 9, "assword: ", 9) == 0) {
//    wlog("-= password prompt =-\n");
    return 1;
  }
  else {
//    wlog("-= not password prompt =- 2\n");
    return 0;
  }
}

int
check_scp_login(char *buf)
{
//  wlog("passwd_failed(): buf = |%s|\n", buf);

  if (strncmp(buf, "Permission denied", 17) == 0) {
//    wlog("password failed\n");
    return LOGIN_BAD;
  }
  else if (strncmp(buf, "bash", 4) == 0) {
//    wlog("program not there.\n");
    return NO_PROG;
  }
  else {
//    wlog("password ok\n");
    return 0;
  }
}

