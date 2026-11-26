#
#   Makefile for demo1
#

CC =  gcc

BIN = demo1.nio

#LIB = -lnsl -lsocket # Solaris
LIB = -lutil

CFLAGS = -I../new_rpc -I../nio_lib -O -Wall -g -DDEBUG -DUNIX

OBJS = ../nio_lib/nio_lib.a ../new_rpc/new_rpc.a ../misc_lib/misc_lib.a

all: $(BIN)

demo1.nio:	demo1.o $(OBJS)
		$(CC) -o $@ demo1.o $(OBJS) $(LIB)

install:
		mkdir -p $(HOME)/nio
		cp *.nio $(HOME)/nio
		mkdir -p $(HOME)/nio/demo1
		cp *.ogg $(HOME)/nio/demo1

clean:
		rm -f *.o *.nio core

new: all install

