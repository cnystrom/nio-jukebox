#
#   Makefile for flip
#

CC =  gcc

BIN = flip.nio

#LIB = -lnsl -lsocket # Solaris
#LIB = -lnsl -lutil
LIB =

CFLAGS = -I../new_rpc -I../nio_lib -I../misc_lib -O -Wall -g -DDEBUG -DUNIX

OBJS = ../nio_lib/nio_lib.a ../new_rpc/new_rpc.a ../misc_lib/misc_lib.a

all: $(BIN)

flip.nio:	flip.o $(OBJS)
		$(CC) -o $@ flip.o $(OBJS) $(LIB)

install:
		mkdir -p $(HOME)/nio
		cp *.nio $(HOME)/nio
		mkdir -p $(HOME)/nio/flip
		cp *.wav $(HOME)/nio/flip

clean:
		rm -f *.o *.nio core

new: all install

