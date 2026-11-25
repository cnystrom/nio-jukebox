#
CC =  gcc
BIN = test
#LIB = # -lutil # OS X
LIB = -lutil  # Linux
 
CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX
 
all: $(BIN)
 
test:		test.o scp_lib.a ../misc_lib/misc_lib.a
		$(CC) -o $@ test.o scp_lib.a ../misc_lib/misc_lib.a $(LIB)
 
scp_lib.a:	scp_lib.o
		ar rcs scp_lib.a scp_lib.o
		ranlib scp_lib.a

test.o:		test.c scp_lib.c scp_lib.h
		$(CC) $(CFLAGS) -c test.c

scp_lib.o:	scp_lib.c scp_lib.h
		$(CC) $(CFLAGS) -c scp_lib.c

install:
		cp *.a ..

new:
		make clean
		make all
 
clean:
		rm -f *.o *.a *.log $(BIN) core a.out
 
