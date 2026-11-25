#!/bin/sh

. ./build.sh

DISTRIB=nlogin.${VERSION}_bin_${BUILD}

mkdir -p ../${DISTRIB}
cp nlogin ../${DISTRIB}
cp *.wav ../${DISTRIB}
cp install.sh ../${DISTRIB}

cd ../${DISTRIB}
mkdir -p fonts
cd fonts
cp ../../nlogin/fonts/* .

cd ../..
tar cvf ${DISTRIB}.tar ${DISTRIB}

scp ${DISTRIB}.tar olenska.newio.org:/export/home/cnystrom

