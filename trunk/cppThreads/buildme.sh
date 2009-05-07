#!/bin/bash
make clean
CXXFLAGS="-ggdb3 -O2" ./configure --libdir=`pwd`/libs --enable-static --disable-shared
make
make install
