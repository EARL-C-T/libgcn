#! /bin/bash
########### this is to make a static avr lib ##############
mkdir avr_build
avr-gcc -c src/GCN.c avr_build/GCN.o
avr_ar rcs avr_build/libGCN.a avr_build/GCN.o
