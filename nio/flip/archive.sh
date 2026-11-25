#!/bin/sh

VERSION=0.004
BUILD=009
DATE=040905

TAR_FILE=flip.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} flip

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

