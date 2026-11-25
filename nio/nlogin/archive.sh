#!/bin/sh

. ./build.sh

TAR_FILE=nlogin.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} nlogin

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

