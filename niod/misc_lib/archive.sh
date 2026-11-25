#!/bin/sh

. ../build.sh

TAR_FILE=misc_lib.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} misc_lib

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

