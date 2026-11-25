#
CC =  gcc
BIN = misc_lib.a
#LIB = # -lutil # OS X
LIB = -lutil  # Linux
 
CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX
 
all: $(BIN)
 
misc_lib.a:	uio.o wlog.o misc_io.o netstring.o url.o tty_echo.o strlcat.o \
		strlcpy.o rand.o path.o
		ar rcs misc_lib.a uio.o wlog.o misc_io.o netstring.o url.o \
		tty_echo.o strlcat.o strlcpy.o rand.o path.o
		ranlib misc_lib.a

tty_echo.o:	tty_echo.c misc_lib.h
		$(CC) $(CFLAGS) -c tty_echo.c

uio.o:		uio.c misc_lib.h
		$(CC) $(CFLAGS) -c uio.c

wlog.o:		wlog.c misc_lib.h
		$(CC) $(CFLAGS) -c wlog.c

misc_io.o:	misc_io.c misc_lib.h
		$(CC) $(CFLAGS) -c misc_io.c

netstring.o:	netstring.c misc_lib.h
		$(CC) $(CFLAGS) -c netstring.c

url.o:		url.c misc_lib.h
		$(CC) $(CFLAGS) -c url.c

strlcat.o:	strlcat.c misc_lib.h
		$(CC) $(CFLAGS) -c strlcat.c

strlcpy.o:	strlcpy.c misc_lib.h
		$(CC) $(CFLAGS) -c strlcpy.c

rand.o:		rand.c misc_lib.h
		$(CC) $(CFLAGS) -c rand.c

path.o:		path.c misc_lib.h
		$(CC) $(CFLAGS) -c path.c

indent:		
		indent -kr -i8 *.h *.c

install:
		cp *.a ..

new:
		make clean
		make all
 
clean:
		rm -f *.o *.a *.log $(BIN) core a.out *~
 
