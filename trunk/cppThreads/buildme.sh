#!/bin/bash
#make clean
CXXFLAGS="-ggdb3 -O0" ./configure --libdir=`pwd`/libs --includedir=`pwd`/libs/include --enable-static --disable-shared
make
#make install
