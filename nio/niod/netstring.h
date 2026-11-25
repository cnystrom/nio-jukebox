//
//  netstring.c
//
//  From:
//    http://cr.yp.to/proto/netstrings.txt
//

#ifndef BUFSIZ
#define BUFZIE  (8192)
#endif

int encode_netstring(char *buf, FILE *fp);
int decode_netstring(char *buf, FILE *fp);

