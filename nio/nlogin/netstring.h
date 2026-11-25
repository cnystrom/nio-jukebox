//
//  netstring.c
//
//  From:
//    http://cr.yp.to/proto/netstrings.txt
//

#ifndef BUFSIZ
#define BUFZIE  (8192)
#endif

#define STDIN     (0)
#define STDOUT    (1)
#define STDERR    (2)

int encode_netstring(char *buf, int fd);
int decode_netstring(char *buf, int fd);

