#
#   Makefile for nio_demo_apps
#

CC =  gcc

BIN = list.nio screen_test.nio char_test.nio string_test.nio box_test.nio dot_test.nio line_test.nio arc_test.nio beep_test.nio mouse_test.nio sound_off.nio startrek.nio

#LIB = -lnsl -lsocket # Solaris
LIB = -lnsl -lutil

CFLAGS = -I../new_rpc -I../nio_lib -O -Wall -g -DDEBUG -DUNIX

OBJS = ../nio_lib/nio_lib.a ../new_rpc/new_rpc.a ../misc_lib/misc_lib.a

all: $(BIN)

list.nio:	list.o $(OBJS)
		$(CC) -o $@ list.o $(OBJS) $(LIB)

char_test.nio:	char_test.o $(OBJS)
		$(CC) -o $@ char_test.o $(OBJS) $(LIB)

string_test.nio:	string_test.o $(OBJS)
		$(CC) -o $@ string_test.o $(OBJS) $(LIB)

box_test.nio:	box_test.o $(OBJS)
		$(CC) -o $@ box_test.o $(OBJS) $(LIB)

dot_test.nio:	dot_test.o $(OBJS)
		$(CC) -o $@ dot_test.o $(OBJS) $(LIB)

line_test.nio:	line_test.o $(OBJS)
		$(CC) -o $@ line_test.o $(OBJS) $(LIB)

arc_test.nio:	arc_test.o $(OBJS)
		$(CC) -o $@ arc_test.o $(OBJS) $(LIB)

screen_test.nio:	screen_test.o $(OBJS)
		$(CC) -o $@ screen_test.o $(OBJS) $(LIB)

play_test.nio:	play_test.o $(OBJS)
		$(CC) -o $@ play_test.o $(OBJS) $(LIB)

beep_test.nio:	beep_test.o $(OBJS)
		$(CC) -o $@ beep_test.o $(OBJS) $(LIB)

mouse_test.nio:	mouse_test.o $(OBJS)
		$(CC) -o $@ mouse_test.o $(OBJS) $(LIB)

sound_off.nio:	sound_off.o $(OBJS)
		$(CC) -o $@ sound_off.o $(OBJS) $(LIB)

startrek.nio:	startrek.o $(OBJS)
		$(CC) -o $@ startrek.o $(OBJS) $(LIB)

install:
		mkdir -p $(HOME)/nio
		cp *.nio $(HOME)/nio
		mkdir -p $(HOME)/nio/startrek
		cp *.jpg $(HOME)/nio/startrek
		cp *.wav $(HOME)/nio/startrek

clean:
		rm -f *.o *.nio core

new: all install

