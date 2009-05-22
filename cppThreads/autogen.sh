#!/bin/bash

autoheader
touch stamp-h
mkdir m4
aclocal
autoconf
autoreconf -fi -I config -I build-aux
automake
rm -rf m4
