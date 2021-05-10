#!/bin/bash

# Usbong Automotive: Image Processing Automation
# Usbong Computer Aided Design (CAD): 3D Tool 
# Usbong Paint Equation
#
# C++ Computer Language and OpenGL
#
# Compile and Link Multiple Source Files
#
# @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
# @author: SYSON, MICHAEL B.
# @date created: 20200930
# @last updated: 20210510
#
# Reference:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20200930

cp -r ./textures ./output/
cp -r ./input ./output/

#rm *.o

g++ -c mainLinux.cpp
g++ -c OpenGLCanvas.cpp
g++ -c MyDynamicObject.cpp
g++ -c RobotShip.cpp
g++ -c Font.cpp
g++ -c Beam.cpp
g++ -c Asteroid.cpp
g++ -c Level.cpp
g++ -c PolygonUtils.cpp
g++ -c CTargaImage.cpp
g++ -c Pilot.cpp
g++ -c UsbongUtils.cpp

#g++ -o mainOutput main.o OpenGLCanvas.o -lGL -lGLU -lglut
# edited by Mike, 20210126
# g++ -o ./output/mainOutputLinux mainLinux.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o Font.o Beam.o Asteroid.o Level.o PolygonUtils.o CTargaImage.o Pilot.o UsbongUtils.o -lGL -lGLU -lglut
g++ -o ./output/UsbongPaintEquationLinux mainLinux.o OpenGLCanvas.o MyDynamicObject.o RobotShip.o Font.o Beam.o Asteroid.o Level.o PolygonUtils.o CTargaImage.o Pilot.o UsbongUtils.o -lGL -lGLU -lglut

#added by Mike, 20210220
cp -r ./*.o ./objectFilesLinux/
