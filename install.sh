#!/bin/bash
# Welcome to CryptoConcurrency Visualization 
#
echo "You can config the compiler for qmake to use by command: qmake -spec <compile-spec>"
echo "qmake specs could be found in /usr/lib/x86_64-linux-gnu/qt5/mkspecs"
echo "CryptoConcurrency Visualization v1.0"
qmake
make

