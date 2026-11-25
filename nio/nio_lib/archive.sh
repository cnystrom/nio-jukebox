#!/bin/sh

VERSION=0.04
BUILD=012
DATE=040905

TAR_FILE=nio_lib.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} nio_lib

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

