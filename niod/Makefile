#
#   Makefile for nio_demo_apps
#

CC =  gcc

BIN = niod

#LIB = -lnsl -lsocket # Solaris
LIB = -lnsl -lutil

CFLAGS = -Imisc_lib -O -Wall -g -DDEBUG -DUNIX

OBJS = misc_lib/misc_lib.a

all: $(BIN)

niod:		niod.o $(OBJS)
		$(CC) -o $@ niod.o $(OBJS) $(LIB)

indent:
		indent -kr -i8 *.c

install:
		mkdir -p $(HOME)/nio
		cp *.nio $(HOME)/nio

clean:
		rm -f *.o $(BIN) *.nio core *~

new: all install

