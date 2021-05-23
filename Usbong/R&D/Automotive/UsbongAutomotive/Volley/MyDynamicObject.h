/*
 * Copyright 2020~2021 Usbong Social Systems, Inc.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @company: USBONG SOCIAL SYSTEMS, INC. (USBONG)
 * @author: SYSON, MICHAEL B. 
 * @date created: 20200930
 * @date updated: 20210523
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//TO-DO: -update: this

#ifndef MYDYNAMICOBJECT_H
#define MYDYNAMICOBJECT_H


//#include "OpenGLCanvas.h"	//added by Mike, 20210522

/*
//edited by Mike, 20201226
//#include <Math.h> //Windows Machine
#include <math.h> //Linux Machine
*/
//TO-DO: -reverify: this
#include <math.h> //Windows and Linux Machines

//added by Mike, 20201217
//Reference: https://stackoverflow.com/questions/34152424/autodetection-of-os-in-c-c;
//answer by: Jeegar Patel, 20151208T0940
//auto-identify if Windows Machine
#ifdef _WIN32
	#include <windows.h> //Windows Machine
#endif
/*
#ifdef linux
    printf("In Linux");
#endif
*/

#include <stdlib.h>
//removed by Mike, 20201226
//#include <stdio.h> //added by Mike, 20201226

//added by Mike, 20210517; removed by Mike, 20210517
//set @OpenGLCanvas.cpp
//#include "UsbongUtils.h"

//added by Mike, 20201207
// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE  = 1;

// index constants for accessing arm and leg array data
const char LEFT  = 0;
const char RIGHT = 1;

	//removed by Mike, 20201201
//const int STANDING_STATE = 0;
//const int WALKING_STATE = 1;

//edited by Mike, 20201201
#define IDLE_MOVING_STATE 0
#define WALKING_MOVING_STATE 1
#define ATTACKING_MOVING_STATE 2 //added by Mike, 20201218

const int INITIALIZING_STATE = 0;
const int MOVING_STATE = 1;
const int IN_TITLE_STATE = 2;
const int DYING_STATE = 3;

//added by Mike, 20210517
const int HIDDEN_STATE = 4,
          ACTIVE_STATE = 5;          

//added by Mike, 20201130
#define FACING_UP 0
#define FACING_DOWN 1
#define FACING_LEFT 2
#define FACING_RIGHT 3
//added by Mike, 20210201
//diagonal
#define FACING_LEFT_AND_UP 4
#define FACING_RIGHT_AND_UP 5
#define FACING_LEFT_AND_DOWN 6
#define FACING_RIGHT_AND_DOWN 7

//added by Mike, 20210517
class UsbongUtils;

//added by Mike, 20210522
//note: add here the class, i.e. classification, filename; 
//no need to use the "include" Command for the header file
class OpenGLCanvas;


class MyDynamicObject
{
private:        
	//TO-DO: -add: collisionBoxes
    float **collisionSpheres;
    int csSize; //to allow multiple spheres
    int maxSize;
    int i;
    bool isCollidable;
	
	//removed by Mike, 20210523
//	UsbongUtils *myUsbongUtils; //added by Mike, 202105017

public:
    float myXPos;
    float myYPos;
    float myZPos;
    
    float myWidth;
    float myHeight;

	//added by Mike, 20210517
    int myXPosAsPixel;
    int myYPosAsPixel;
    int myZPosAsPixel;    
    int myWidthAsPixel;
    int myHeightAsPixel;
	
	//added by Mike, 20201115
    int myWindowWidth;
    int myWindowHeight;
    
    //added by Mike, 20210522
    float fGridSquareWidth;
    float fGridSquareHeight;
	OpenGLCanvas *myOpenGLCanvas;
    
	//added by Mike, 202105023
    UsbongUtils *myUsbongUtils;
    
    //added by Mike, 20210517
	int currentState;
	

/*	//removed by Mike, 20201226
	//added by Mike, 20201226
   	int myKeysDown[4]; //TO-DO: -update: this to include diagonal directional movement
*/

	//edited by Mike, 20201113
//    MyDynamicObject(float xPos = 0.0f, float yPos = 0.0f, float zPos= 300.0f ): myXPos(xPos), myYPos(yPos), myZPos(zPos) 
	//edited by Mike, 20201115
/*    MyDynamicObject(float xPos = 0.0f, float yPos = 0.0f, float zPos= 0.0f ): myXPos(xPos), myYPos(yPos), myZPos(zPos) 
    //{myXPos=0.0f; myYPos=0.0f; myZPos=300.0f;}
    {}
*/
	//TO-DO: -update: to use grid as window Width and window Height instead of windowWidth/100 and windowHeight/100
	//Note: 
	//fGridSquareWidth = myWindowWidth/iColumnCountMax/100.0;
	//fGridSquareHeight = myWindowHeight/iRowCountMax/100.0;
    MyDynamicObject(float xPos=0.0f, float yPos=0.0f, float zPos=0.0f, int windowWidth=0, int windowHeight=0 ): myXPos(xPos), myYPos(yPos), myZPos(zPos), myWindowWidth(windowWidth/100), myWindowHeight(windowHeight/100)
	{
		currentState=ACTIVE_STATE;
	}	

	//added by Mike, 20210517
	~MyDynamicObject();

	//added by Mike, 20210517
	bool isActive(){
         if (currentState==ACTIVE_STATE)
           return true;
         else return false;
    }

	//added by Mike, 20210517
	void setUsbongUtils(UsbongUtils* c);

    virtual void hitBy(MyDynamicObject* mdo);
        
    //collision stuff
    bool checkIsCollidable();
    void setCollidable(bool c);

    void initializeCollisionSpheres(int ms);
    
    void addSphere(float dx, float dy, float dz, float r);
	
	float** getCollisionSpheres();

    int getNumSpheres();
    
    virtual float getX()=0;
    virtual float getY()=0;
    virtual float getZ()=0;
	virtual float getWidth()=0;
    virtual float getHeight()=0;

	//added by Mike, 20210517
/*	
    virtual int getXAsPixel()=0;
    virtual int getYAsPixel()=0;
    virtual int getZAsPixel()=0;
	virtual int getWidthAsPixel()=0;
    virtual int getHeightAsPixel()=0;
*/
	virtual int getXAsPixel()
    {
       return myXPosAsPixel;
    }
    virtual int getYAsPixel()
    {
       return myYPosAsPixel;
    }
    virtual int getZAsPixel()
    {
       return myZPosAsPixel;
    }
    virtual int getWidthAsPixel()
    {
       return myWidthAsPixel;
    }
    virtual int getHeightAsPixel()
    {
       return myHeightAsPixel;
    }
	
	//added by Mike, 20201217
    virtual void draw();	

	//added by Mike, 20210424
    virtual void setXPos(float fX) {
		myXPos=fX;
	}
    virtual void setZPos(float fZ) {
		myZPos=fZ;
	}
    virtual void setYPos(float fY) {
		myYPos=fY;
	}

    float getDistance(float x1, float y1, float z1, float x2, float y2, float z2);
    
    bool checkCollision(MyDynamicObject* mdo1, MyDynamicObject* mdo2);
    void collideWith(MyDynamicObject* mdo);
	
	//added by Mike, 20210517
	bool collideWithPressedCoordPos(int pressedCoordPosX, int pressedCoordPosY);

	//edited by Mike, 20210219
    //bool isIntersectingRect(MyDynamicObject* mdo1, MyDynamicObject* mdo2);
    virtual bool isIntersectingRect(MyDynamicObject* mdo1, MyDynamicObject* mdo2);

	//added by Mike, 20201226
/*	//removed by Mike, 20201226
	void keyDown(int keyCode) {
		myKeysDown[keyCode] = TRUE;
	}
	
    void keyUp(int keyCode) {
		myKeysDown[keyCode] = FALSE;	
	}
*/

	//added by Mike, 20210522
	virtual void setOpenGLCanvas(OpenGLCanvas* c, float fSideLengthInput) {
		myOpenGLCanvas = c;
		//TO-DO: -update: this
		fGridSquareWidth = fSideLengthInput;
		fGridSquareHeight = fSideLengthInput;		
	};
    
    //added by Mike, 20201016
    virtual void destroy();
};

#endif
