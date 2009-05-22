#!/bin/bash

if [ ! -d m4 ]; then mkdir m4; fi
autoheader
touch stamp-h
aclocal
autoconf
autoreconf -fi -I config -I build-aux
automake
