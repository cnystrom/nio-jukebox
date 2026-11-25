#!/bin/sh

cd misc_lib
make indent
make clean
cd ..

make indent
make clean

cd /var/tmp
rm -f *.log
rm -f *.tmp

