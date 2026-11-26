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

Updated November 2026 so the server side builds with a current gcc
on Linux:

- `niod`: run `niod/compile.sh`. The program's own `getline()` is now
  `my_getline()`, so it no longer clashes with the C library.
- `nio/` (`misc_lib`, `new_rpc`, `nio_lib`, `niod`, `demo1`, `flip`,
  `jukebox`, `nio_demo_apps`): run `make` in each directory, in that
  order.
- `-lnsl` was dropped from the Makefiles, because current glibc no
  longer has libnsl.
- `strlcpy` and `strlcat` in `niod/misc_lib` are new, original
  replacements for the removed third-party files.

The NIO client `nio/nlogin` still does not build. It needs the
removed third-party font, text and colour files.

`niod/clean.sh` also deletes every `*.log` and `*.tmp` file in
`/var/tmp`.
