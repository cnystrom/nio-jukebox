#!/bin/sh

VERSION=004
BUILD=010
DATE=040905

TAR_FILE=nio_demo_apps.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} nio_demo_apps

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

