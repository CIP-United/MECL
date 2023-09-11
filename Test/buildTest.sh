#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

if [ ! -f "libMECL.a" ]; then
	echo "Build $1 FAIL!"
	echo "There are no exising libMECL.a !"
	exit
fi

echo "Building $1"
output="${1%.*}"
host_arch=`arch`
if [[ $host_arch =~ "mips64" ]]; then
    gcc -o $output.bin $1 BasicFramework.c -I ../Include/ -L./ -lMECL -lm -g -mabi=32
else
    gcc -o $output.bin $1 BasicFramework.c -I ../Include/ -L./ -lMECL -lm -g
fi
if [ "$?" != "0" ] ; then
    echo "Build $1 FAILED!!!"
    exit
fi
echo "Build $1 done"

