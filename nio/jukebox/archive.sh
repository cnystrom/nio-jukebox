#!/bin/sh

VERSION=0.004
BUILD=009
DATE=040905

TAR_FILE=jukebox.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} jukebox

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

