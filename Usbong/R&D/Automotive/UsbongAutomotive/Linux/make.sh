#!/bin/bash

# Usbong Halimbawa: Image Processing Automation
# C++ Computer Language and OpenGL
#
# Compile and Link Multiple Source Files
#
# @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
# @author: SYSON, MICHAEL B.
# @date created: 20200930
# @last updated: 20201121
#
# Reference:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20200930

g++ -c main.cpp
g++ -c OpenGLCanvas.cpp
g++ -c MyDynamicObject.cpp
g++ -c RobotShip.cpp
g++ -c Font.cpp
g++ -c Beam.cpp
g++ -c Asteroid.cpp
g++ -c Level.cpp
g++ -c PolygonUtils.cpp

#g++ -o mainOutput main.o OpenGLCanvas.o -lGL -lGLU -lglut
g++ -o mainOutput main.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o Font.o Beam.o Asteroid.o Level.o PolygonUtils.o -lGL -lGLU -lglut
