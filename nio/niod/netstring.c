//
//  netstring.c
//
//  From:
//    http://cr.yp.to/proto/netstrings.txt
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../misc_lib/wlog.h"
#include "netstring.h"

#ifndef BUFSIZ
#define BUFZIE  (8192)
#endif

int
encode_netstring(char *buf, FILE *fp)
{
  int len;

  len = strlen(buf);

  if (len <= 0 || len > BUFSIZ) {
    wlog("encode_netstring(): length bad.\n");
    return -1;
  }

  if (fprintf(fp, "%u:", len) < 0) {
    wlog("encode_netstring(): length bad.\n");
    return -2;
  }

  if (fwrite(buf, 1, len, fp) < len) {
    wlog("encode_netstring(): write failed.\n");
    return -3;
  }

  if (putc((','), fp) < 0) {
    wlog("encode_netstring(): missing comma.\n");
    return -4;
  }

  return(len);
}

int
decode_netstring(char *buf, FILE *fp)
{
  int len;

  // >999999999 bytes is bad 
  if (fscanf(fp, "%9u", &len) < 1) {
    wlog("decode_netstring(): length bad.\n");
    return -1;
  }

  if (len <= 0 || len > BUFSIZ) {
    wlog("decode_netstring(): length bad.\n");
    return -2;
  }

  if (getc(fp) != ':') {
    wlog("decode_netstring(): missing colon.\n");
    return -3;
  }

  if (fread(buf, 1, len, fp) < len) {
    wlog("decode_netstring(): read failed.\n");
    return -4;
  }

  if (getc(fp) != ',') {
    wlog("decode_netstring(): missing comma.\n");
    return -5;
  }

  *(buf + len) = 0;

  return(len);
}

/*
int
main(void)
{
  char s[BUFSIZ];

  encode_netstring("This is a test", stdout);

  printf("\nINPUT> ");

  // cut and paste above output into here to test
  decode_netstring(s, stdin);

  printf("\n");

  printf("s = |%s|\n", s);

  exit(0);
}
*/

