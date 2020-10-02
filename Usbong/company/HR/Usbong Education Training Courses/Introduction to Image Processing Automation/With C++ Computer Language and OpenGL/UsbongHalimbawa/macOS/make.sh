#!/bin/bash

# Usbong Halimbawa: Image Processing Automation
# C++ Computer Language and OpenGL
#
# Compile and Link Multiple Source Files
#
# @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
# @author: SYSON, MICHAEL B.
# @date created: 20200930
# @last updated: 20201003
#
# Reference:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20200930

g++ -c main.cpp
g++ -c OpenGLCanvas.cpp
g++ -c MyDynamicObject.cpp
g++ -c RobotShip.cpp

#g++ -o mainOutput main.o OpenGLCanvas.o -lGL -lGLU -lglut
#edited by Mike, 20201003
#g++ -o mainOutput main.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o -lGL -lGLU -lglut
# note: macOS command
g++ -o mainOutput main.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o -framework OpenGL -framework GLUT
