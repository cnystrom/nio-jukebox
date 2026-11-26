/******************************************************************************
 *
 *    buffer.c
 *
 *    Copyright (C) 2005  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    E-Mail: cnystrom@gmail.com
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../misc_lib/wlog.h"
#include "types.h"
#include "buffer.h"

#define ERR1 "buffer overflow"

static byte buf[BUF_SIZE] = {0};
static int  buf_write_index;
static int  buf_read_index; 

void
reset_buf(void)
{
  buf_read_index = 0;
  buf_write_index = 0;
}

/*
byte *
get_buf(void)
{
  return(buf);
}

int
get_buf_index(void)
{
  return(buf_write_index);
}

void
set_buf_index(int i)
{
  buf_write_index = i;
}
*/

void
display_buf(void)
{
  int i;

  wlog("\n----\n");
  wlog("buffer =\n");
  for (i = 0; i < buf_write_index; i++) {
    wlog("buf[%d] = %d ", i, buf[i]);

    if (buf[i] > 32) {
      wlog("%c\n", buf[i]);
    }
    else {
      wlog("\n");
    }
  }
  wlog("----\n\n");
}

void
pack_int8(int8 int8)
{
  if ((buf_write_index + INT8_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_int8(): %s\n", ERR1);
    return;
  }

  buf[buf_write_index++] = int8;
}

int8
unpack_int8(void)
{
  if ((buf_read_index + INT8_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_int8(): %s\n", ERR1);
    return(-1);
  }

  return(buf[buf_read_index++]);
}

void
pack_int16(int16 i1)
{
  int   i;
  byte *bp;
  int16 i2;

//  printf("pack_int16(): buf_write_index = %d\n", buf_write_index);
//  printf("pack_int16(): buf_read_index = %d\n", buf_write_index);

  if ((buf_write_index + INT16_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_int16(): %s\n", ERR1);
    return;
  }

  i2 = htons(i1);

  bp = (byte *) &i2;

  for (i = 0; i < INT16_SIZE; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

int16
unpack_int16(void)
{
  int i;
  byte *bp;
  int16 i1;

//  printf("unpack_int16(): buf_write_index = %d\n", buf_write_index);
//  printf("unpack_int16(): buf_read_index = %d\n", buf_write_index);

  if ((buf_read_index + INT16_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_int16(): %s\n", ERR1);
    return(-1);
  }

  bp = (byte *) &i1;

  for (i = 0; i < INT16_SIZE; i++) {
    *(bp++) = buf[buf_read_index++];
  }

//  printf("unpack_int16(): int16 = %d\n", int16);

  return(ntohs(i1));
}

void
pack_int32(int32 i1)
{
  int   i;
  byte *bp;
  int32 i2;

//  printf("pack_int32(): buf_write_index = %d\n", buf_write_index);
//  printf("pack_int32(): buf_read_index = %d\n", buf_write_index);

  if ((buf_write_index + INT32_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_int32(): %s\n", ERR1);
    return;
  }

  i2 = htonl(i1);

  bp = (byte *) &i2;

  for (i = 0; i < INT32_SIZE; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

int32
unpack_int32(void)
{
  int i;
  byte *bp;
  int32 i1;

//  printf("unpack_int32(): buf_write_index = %d\n", buf_write_index);
//  printf("unpack_int32(): buf_read_index = %d\n", buf_write_index);

  if ((buf_read_index + INT32_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_int32(): %s\n", ERR1);
    return(-1);
  }

  bp = (byte *) &i1;

  for (i = 0; i < INT32_SIZE; i++) {
    *(bp++) = buf[buf_read_index++];
  }

  return(ntohl(i1));
}

void
pack_string(char *s)
{
  int   i;
  Uint16 len;
  byte *bp;

  len = strlen(s) + 1;  // Add the NUL termination

//  printf("pack_string(): len = %d\n", len);

  if ((buf_write_index + INT16_SIZE + len) >= BUF_SIZE) {
    fprintf(stderr, "pack_string(): %s\n", ERR1);
    return;
  }

  pack_int16(len);

  bp = (byte *) s;

  for (i = 0; i < len; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

void
unpack_string(char *s)
{
  int i;
  Uint16 len;
  byte *bp;

  if ((buf_read_index + INT16_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_string(): %s\n", ERR1);
    return;
  }

  len = unpack_int16();

//  printf("unpack_string(): len = %d\n", len);

  if ((buf_read_index + len) > buf_write_index) {
    fprintf(stderr, "unpack_string(): %s\n", ERR1);
    return;
  }

  bp = (byte *) s;

//  printf("unpack_string(): buf_read_index = %d\n", buf_read_index);

  for (i = 0; i < len; i++) {
    *(bp++) = buf[buf_read_index++];
  }

  return;
}

int
write_buffer(int fd)
{
  int i, len;

  len = buf_write_index;

//  usleep(1);

  i = write(fd, buf, len);

  if (i != len) {
    wlog("write_buffer(): write error\n");
    exit(-1);
  }

//  wlog("\nbuffer written...\n");
//  display_buf();

  return(i);
}

int
read_buffer(int fd)
{
  reset_buf();

//  wlog("********\n");

//  sleep(1);
//  wlog("read_buffer(): reading...\n");
  buf_write_index = read(fd, buf, BUF_SIZE);

  if (buf_write_index <= 0) {
    wlog("read_buffer(): read failed\n");
    exit(-1);
  }

//  wlog("read_buffer(): buf_write_index = %d\n", buf_write_index);
//  display_buf();

  return(buf_write_index);
}

int
wr_buffer(int fd_out, int fd_in)
{
  int bc, len;

  len = buf_write_index;

//  wlog("wr_buffer(): sleep(1)...\n");
//  usleep(1);

//  wlog("wr_buffer(): calling write()...\n");

  bc = write(fd_out, buf, len);

  if (bc != len) {
    wlog("wr_buffer(): write error\n");
    exit(-1);
  }

  bc = read(fd_in, buf, BUF_SIZE);

  while (bc <= 0) {
    if (bc == 0) {  // end of input: the client has gone away
      wlog("wr_buffer(): connection closed\n");
      exit(-1);
    }
    wlog("wr_buffer(): read failed. re-writing... \n");
    write(fd_out, buf, len); // Maybe they did not get message?
    wlog("wr_buffer(): re-reading... \n");
    bc = read(fd_in, buf, BUF_SIZE);
  }

  buf_write_index = bc;

//  wlog("wr_buffer(): buf_write_index = %d\n", buf_write_index);
//  display_buf();

  return(buf_write_index);
}

bool
cmp_buf(char *s)
{
  int len;

  len = strlen(s);

  if (strncmp(buf, s, len) == 0) {
    return(TRUE);
  }
  else {
    return(FALSE);
  }
}

/*
void
pack_buffer(void)
{
  int8 v1 = CHAR_MAX;
  int16 w1 = SHRT_MAX;
  int32 x1 = INT_MAX;
  char s1[] = "Test";

  reset_buf();

  pack_int8(v1);
  pack_int16(w1);
  pack_int32(x1);
  pack_string(s1);
}

void
unpack_buffer(void)
{
  int8 v2 = 0;
  int16 w2 = 0;
  int32 x2 = 0;
  char s2[20] = "";

  v2 = unpack_int8();
  w2 = unpack_int16();
  x2 = unpack_int32();
  unpack_string(s2);

  wlog("v2 = %d\n", v2);
  wlog("w2 = %d\n", w2);
  wlog("x2 = %d\n", x2);
  wlog("s2 = |%s|\n\n", s2);
}
*/
/*
#ifndef STDOUT
#define STDOUT  (1)
#endif

int
main(void)
{
  wlog_open_fd(STDOUT);

  pack_buffer();

  display_buf();

  unpack_buffer();

  wlog_close();

  exit(0);
}
*/

