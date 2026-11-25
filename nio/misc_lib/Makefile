#
CC =  gcc
BIN = misc_lib.a
#LIB = # -lutil # OS X
LIB = -lutil  # Linux
 
CFLAGS = -I.. -O -Wall -g -DDEBUG -DUNIX
 
all: $(BIN)
 
misc_lib.a:	uio.o wlog.o tty_echo.o
		ar rcs misc_lib.a uio.o wlog.o tty_echo.o
		ranlib misc_lib.a

tty_echo.o:	tty_echo.c tty_echo.h
		$(CC) $(CFLAGS) -c tty_echo.c

uio.o:		uio.c uio.h
		$(CC) $(CFLAGS) -c uio.c

wlog.o:		wlog.c wlog.h
		$(CC) $(CFLAGS) -c wlog.c

install:
		cp *.a ..

new:
		make clean
		make all
 
clean:
		rm -f *.o *.a *.log $(BIN) core a.out
 
