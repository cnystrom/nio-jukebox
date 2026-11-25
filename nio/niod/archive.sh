#!/bin/sh

VERSION=0.04
BUILD=013
DATE=050405

TAR_FILE=niod.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} niod

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

