#! /bin/bash 
########################## bash install script ###########################
mkdir build
gcc -c -fpic src/GCN.c -o build/GCN.o
gcc -shared -o build/libGCN.so build/GCN.o
