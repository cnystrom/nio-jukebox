#the compiler
CC = gcc

#compiler options

# Linux
COPTS = -O3 -g -Wall $(shell sdl-config --cflags)
# Solaris
#COPTS = -O3 -g -Wall -I/usr/local/include/SDL -D_REENTRANT -Wno-deprecated 

#header files
INCLUDES = \
	-I../new_rpc \
	-I../scp_lib \
	-I../misc_lib \
	-I. \
	$(NULL)

#library directories
LIBDIRS = \
	$(NULL)

NRPC_LIB = ../new_rpc/new_rpc.a
#NIO_LIB = ../nio_lib/nio_lib.a
#SSH_LIB = ../ssh_lib/ssh_lib.a
SCP_LIB = ../scp_lib/scp_lib.a
MISC_LIB = ../misc_lib/misc_lib.a

#libraries to link with
LIBS = \
	-lutil \
	-lSDL_ttf \
	-lSDL_image \
	-lSDL_mixer \
	$(NRPC_LIB) \
	$(SCP_LIB) \
	$(MISC_LIB) \
	$(NULL)

#all compiler flags
CFLAGS = $(COPTS) $(INCLUDES) -DUNIX

#all linker options and libs
LFLAGS = $(LIBDIRS) $(shell sdl-config --libs) -lSDL_mixer

#default compilation rules
%.o:	%.c
	$(CC) -c $< $(CFLAGS) -o $@

#local headers to depend on
HEADERS = \
	$(NULL)

#files to compile
CCFILES = \
	colors.c \
	SDL_prim.c \
	screen.c \
	misc_io.c \
	fonts.c \
	images.c \
	text.c \
	home_dir.c \
	file_xfr.c \
	nio_sdl.c \
	mouse.c \
	keyboard.c \
	playlib.c \
	sound.c \
	url.c \
	misc.c \
	term.c \
	text_box.c \
	netstring.c \
	print_func.c \
	loop.c \
	rpc.c \
	main.c \
	$(NULL)

#all local .o files
OBJS =  ${CCFILES:.c=.o}

default: nlogin

nlogin: $(OBJS) $(HEADERS) $(NRPC_LIB) $(MISC_LIB) $(SCP_LIB)
	$(CC) $(LFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	rm -f core $(OBJS) nlogin *~

new: clean default

distrib:
	./distrib.sh

install:
	./install.sh

