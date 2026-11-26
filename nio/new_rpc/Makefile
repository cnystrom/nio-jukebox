#
CC =  gcc
#BIN = buffer
BIN = server client
LIB =  # Linux
#LIB = -lnsl -lsocket # Solaris

CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX

all: $(BIN)

server:		server.o example.o new_rpc.a ../misc_lib/misc_lib.a
		$(CC) -o $@ server.o example.o new_rpc.a ../misc_lib/misc_lib.a

client:		client.o example.o new_rpc.a ../misc_lib/misc_lib.a
		$(CC) -o $@ client.o example.o new_rpc.a ../misc_lib/misc_lib.a $(LIB)

buffer:		buffer.o ../misc_lib/misc_lib.a
		$(CC) -o $@ buffer.o ../misc_lib/misc_lib.a $(LIB)

new_rpc.a:	new_rpc.o buffer.o sock_lib.o
		ar rcs new_rpc.a new_rpc.o sock_lib.o buffer.o
		ranlib new_rpc.a

sock_lib.o:	sock_lib.c sock_lib.h
		$(CC) $(CFLAGS) -c sock_lib.c

buffer.o:	buffer.c buffer.h types.h
		$(CC) $(CFLAGS) -c buffer.c

new_rpc.o:	new_rpc.c new_rpc.h buffer.h sock_lib.h
		$(CC) $(CFLAGS) -c new_rpc.c

example.o:	example.c example.h
		$(CC) $(CFLAGS) -c example.c

server.o:	server.c example.h new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c server.c

client.o:	client.c example.h new_rpc.h sock_lib.h
		$(CC) $(CFLAGS) -c client.c

install:
		cp *.a ..

new:		clean all

clean:
		rm -f *.o *.a a.out $(BIN) core .*.swp

