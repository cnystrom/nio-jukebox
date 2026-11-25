# nio-jukebox

NIO (New IO) plus the newest niod.

NIO is a remote display system and internet service: a library you can
link into programs, a server, a client (`nlogin`), and example programs.
The original announcement describes it as a set of RPC calls to manage
an SDL client remotely — "a poor man's X-Windows, although it is not a
desktop system."

`niod` is the NIO daemon / test server (headers 2002, 2005; the binary
banner in the source is "NIOd Test Server 0.10").

## Origin

From Chris Nystrom's personal source archive (the hallie tree), posted
publicly at his request. This repo uses the newest `nio` and `niod`
trees. Older snapshots (`niod.old`, `niod.012`) were not included.

## Pages

Chris's old programs page is at https://nystrom.family/chris/old/programs.html.
All of Chris's code: https://nystrom.family/chris/code/

## License

Chris's files are typically under the GNU GPL 2 or LGPL 2.1; see each
header.

The GNU GPL 2 (or later) text is in LICENSE; the GNU LGPL 2.1 (or later) text is in COPYING.LESSER.

## Third-party files removed

- Todd C. Miller `strlcat.c` / `strlcpy.c` (under `niod/misc_lib/`)
- Bob Pendleton font/text/misc files in `nio/nlogin/`
- Ryan McGuigan `SDL_prim.c` / `SDL_prim.h`
- David Olofson `speaker.c` / `speaker.h`
- Eric S. Raymond `playlib.c` / `playlib.h`
- Sun Microsystems / Tcl-Tk 8.4.2 `colors.c` / `colors.h`
- Sam Lantinga SDL types file `nio_lib/nio_types.h.old`
- GNU FreeFont documentation under `nlogin/fonts/`
- Media (`.ogg`, `.jpg`) and compiled binaries

## Build

- `niod`: default gcc and `-std=gnu89` fail because the program defines
  its own `getline`. `-std=c89` fails on C++-style `//` comments in the
  sources. It did not build on a current gcc without changing the code,
  which was not done.
- The NIO client and libraries expect SDL. They were not built here.
