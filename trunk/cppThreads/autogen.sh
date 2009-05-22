#!/bin/bash

mkdir m4
autoheader
touch stamp-h
aclocal
autoconf
autoreconf -fi -I config -I build-aux
automake
rm -rf *m4
