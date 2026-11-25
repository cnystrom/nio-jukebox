#
#   Makefile for jukebox
#

CC =  gcc

BIN = jukebox.nio

#LIB = -lnsl -lsocket # Solaris
#LIB = -lnsl -lutil
LIB =

CFLAGS = -I../new_rpc -I../nio_lib -O -Wall -g -DDEBUG -DUNIX

OBJS = ../nio_lib/nio_lib.a ../new_rpc/new_rpc.a ../misc_lib/misc_lib.a

all: $(BIN)

jukebox.nio:	jukebox.o $(OBJS)
		$(CC) -o $@ jukebox.o $(OBJS) $(LIB)

install:
		mkdir -p $(HOME)/nio
		cp *.nio $(HOME)/nio
		mkdir -p $(HOME)/nio/jukebox
		cp songs/*.ogg $(HOME)/nio/jukebox

clean:
		rm -f *.o *.nio core

new: all install

