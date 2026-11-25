/*
 * url.h
 *
 */

#ifndef URL_H
#define URL_H

#ifndef MAX_LINE_LEN
#define MAX_LINE_LEN	 (80)
#endif

#define MAX_SERVICE_LEN  (6)
#define MAX_USERNAME_LEN (16)
#define MAX_SERVER_LEN   (80)
#define MAX_PORT_LEN     (8)
#define MAX_EXT_LEN      (5)

typedef struct
{
  char service[MAX_SERVICE_LEN];
  char username[MAX_USERNAME_LEN];
  char server[MAX_LINE_LEN];
  char port[MAX_PORT_LEN];
  char program[MAX_LINE_LEN];
  char extension[MAX_EXT_LEN];
} url;

void parse_url(url *, char *);
void print_url(url *);

#endif /* URL_H */

