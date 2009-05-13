#!/bin/bash

autoheader
touch stamp-h
aclocal
autoconf
autoreconf -fi -I config -I build-aux
automake
