#!/bin/bash

# Usbong CAD: Computer-Aided Design
# C Computer Language
#
# Compile and Link Multiple Source Files
#
# @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
# @author: SYSON, MICHAEL B.
# @date created: 20201209
# @last updated: 20201209
#
# Reference:
# 1) //Reference: https://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings;
# last accessed: 20201209

g++ -c main.c

#g++ -o mainOutput main.o OpenGLCanvas.o -lGL -lGLU -lglut
g++ -o usbongCADMainOutput main.o
