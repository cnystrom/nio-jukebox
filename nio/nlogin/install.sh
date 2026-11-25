#!/bin/sh
#
#    nlogin
#
#    install.sh
#

LOCAL_DIR=/usr/local
SHARE_DIR=/usr/share/nlogin

echo -----------------------
echo Checking Directories...
echo -----------------------

if [ ! -d ${LOCAL_DIR}/bin ]
then
  echo "mkdir ${LOCAL_DIR}/bin"
  mkdir mkdir ${LOCAL_DIR}/bin
fi

if [ ! -d ${SHARE_DIR} ]
then
  echo "mkdir ${SHARE_DIR}"
  mkdir ${SHARE_DIR}
fi

if [ ! -d ${SHARE_DIR}/fonts ]
then
  echo "mkdir ${SHARE_DIR}/fonts"
  mkdir mkdir ${SHARE_DIR}/fonts
fi

echo -------------------------------
echo Installing client and fonts...
echo -------------------------------

cp nlogin ${LOCAL_DIR}/bin

cp *.wav ${SHARE_DIR}

cd fonts
cp * ${SHARE_DIR}/fonts

echo Done!

