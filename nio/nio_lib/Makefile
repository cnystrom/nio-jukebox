#
# Makefile for nio_lib.o
#

CC =  gcc

CFLAGS = -I../new_rpc -O -Wall -g -DDEBUG -DUNIX

all:		nio_lib.a

nio_lib.a:	nio_lib.c nio_lib.h nio_font.h nio.h ../new_rpc/new_rpc.a
		$(CC) $(CFLAGS) -c nio_lib.c 
		ar rcs nio_lib.a nio_lib.o 
		ranlib nio_lib.a

install:
		cp *.a ..

clean:
		rm -f *.o *.a core .*.swp

