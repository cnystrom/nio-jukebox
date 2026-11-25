#!/bin/sh

VERSION=0.09
BUILD=050
DATE=112505

TAR_FILE=niod.${VERSION}_src_${BUILD}_${DATE}.tar

./clean.sh

cd ..

tar cvf ${TAR_FILE} niod

gzip ${TAR_FILE}

scp ${TAR_FILE}.gz cnystrom@olenska.newio.org:/export/home/cnystrom

