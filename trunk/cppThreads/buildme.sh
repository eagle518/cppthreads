#!/bin/bash
make clean
CXXFLAGS="-ggdb3 -O0" ./configure --libdir=`pwd`/libs --enable-static --disable-shared
make
