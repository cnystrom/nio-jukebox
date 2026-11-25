#
#   Makefile for nio_demo_apps
#

CC =  gcc

BIN = niod

#LIB = -lnsl -lsocket # Solaris
LIB = -lnsl -lutil

CFLAGS = -I../misc_lib -I../nio_lib -O -Wall -g -DDEBUG -DUNIX

OBJS = ../misc_lib/misc_lib.a

all: $(BIN)

niod:		niod.o netstring.o $(OBJS)
		$(CC) -o $@ niod.o netstring.o $(OBJS) $(LIB)

install:
		mkdir -p $(HOME)/nio
		cp *.nio $(HOME)/nio

clean:
		rm -f *.o $(BIN) core

new: all install

