#!/bin/sh

VERSION=0.04
BUILD=014
DATE=040905

TAR_FILE=new_rpc.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} new_rpc

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

