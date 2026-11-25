//
//   ssh_lib.h
//
//   12/06/04 - Chris Nystrom <cnystrom@gmail.com>
//
//   Inspired by script.c in RedHat FC2
//

#ifndef UIO
#include "../misc_lib/uio.h"
#endif

#define USE_READ  (0)
#define USE_UIO   (1)

#define LOGIN_BAD  (1)
#define NO_PROG    (2)

#ifndef BUFSIZ
#define BUFSIZ (8192)
#endif

int  scp_file(char *from_file, char *to_file, char *passwd);
int  call_scp(char *from_file, char *to_file);

int  read_scp(byte *obuf, int count, int uio);
int  write_scp(byte *buf);

void display_scp(void);

int  verify_scp_passwd(char *passwd);
int  scp_passwd_prompt(char *buf);
int  check_scp_login(char *buf);

void done_scp(void);

