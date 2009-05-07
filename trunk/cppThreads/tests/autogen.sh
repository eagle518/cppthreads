#!/bin/bash

autoheader
touch stamp-h
aclocal
autoconf
autoreconf -fi
automake
