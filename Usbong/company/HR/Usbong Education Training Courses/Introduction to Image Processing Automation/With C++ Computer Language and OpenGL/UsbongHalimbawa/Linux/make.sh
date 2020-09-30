#!/bin/bash

# Usbong Halimbawa: Image Processing Automation
# C++ Computer Language and OpenGL
#
# Compile and Link Multiple Source File
#
# @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
# @author: SYSON, MICHAEL B.
# @date created: 20200930
# @last updated: 20200930
#
# Reference:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20200930

g++ -c main.cpp
g++ -c OpenGLCanvas.cpp
g++ -o mainOutput main.o OpenGLCanvas.o -lGL -lGLU -lglut
