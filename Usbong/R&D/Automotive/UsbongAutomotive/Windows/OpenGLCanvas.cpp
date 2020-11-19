/*
 * Copyright 2020 Usbong Social Systems, Inc.
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
 * @date created: 20200926
 * @date updated: 20201119
 *
 * References:
 * 1) https://www.mathsisfun.com/sine-cosine-tangent.html;
 * last accessed: 20201026
 * 
 * 2) https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
 * last accessed: 20201026
 * 
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: "Canvas" to "Engine"?
//TO-DO: -update: this
  
//#include <SDL.h>
//edited by Mike, 20200929

#include <windows.h> //Windows Machine

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include <stdio.h>
//#include <math.h>

#include "OpenGLCanvas.h"

//added by Mike, 20201001
#include "RobotShip.h"

//added by Mike, 20201010
#include "Font.h"

//added by Mike, 20201118
#include "Level.h"

//removed by Mike, 20200929
//TO-DO: -add: these 
/*
#include "PolygonUtils.h"

#include "RobotShip.h"
#include "Enemy.h"
#include "Beam.h"
#include "font.h"
#include "Asteroid.h"
*/

//added by Mike, 20201013
#include "Beam.h"
//added by Mike, 20201016
#include "Asteroid.h"

//#include "Sound.h"

//#include "DynamicObject.h"

//#include "glfont.h"

//removed by Mike, 20201014
//int i;

//TO-DO: -reverify: KEY_D!=OK; KEY_RIGHT=OK
//TO-DO: -reverify: KEY_W!=OK; KEY_UP=OK

//added by Mike, 20201001
enum Keys
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	//edited by Mike, 20201013
	KEY_ENTER,
	//TO-DO: -verify: gamepad
	KEY_A,
	KEY_D,
	KEY_W,
	KEY_S,

	KEY_J,
	KEY_L,
	KEY_I,
	KEY_K
};


/*	//removed by Mike, 20200929
typedef struct
{
    GLubyte id_field_length;
    GLubyte color_map_type;
    GLubyte image_type_code;
    GLubyte ignore[9];
    GLushort width;
    GLushort height;
    GLubyte image_pixel_size;
    GLubyte image_descriptor;
} TARGA_HEADER;
*/

OpenGLCanvas::OpenGLCanvas()
{
  myRepaintCounter=0;
  myRepaintDelay=20;
}

OpenGLCanvas::~OpenGLCanvas()
{
}

bool OpenGLCanvas::init()
{	
	//TO-DO: -receive: values from main.cpp
	//edited by Mike, 20201115
/*    myWindowWidth=640;
    myWindowHeight=640;
*/
    myWindowWidth=2048;
    myWindowHeight=2048;
    
    //added by Mike, 20201023
    myCanvasPosX=-3.2f;//0.0f;
	myCanvasPosY=-1.0f;//0.0f;
	myCanvasPosZ=-3.2f;//0.0f;
    myCanvasEyePosX=0.0f;
    
    //edited by Mike, 20201025
	myCanvasStepX=0.3f;//0.32f;//0.3f;//0.1f;
	myCanvasStepY=0.3f;//0.32f;//0.3f;//0.1f;
	myCanvasStepZ=0.3f;//0.32f;//0.3f;//0.1f;
//	myCanvasEyeStepX=0.3f; //removed by Mike, 20201026
	
	//added by Mike, 20201025; edited by Mike, 20201026
	//add +0.5f to turn right without turning left first
	myCanvasLookAtAngle=-90.0f+0.5f;//-90.0f;
	
	//added by Mike, 20201024; removed by Mike, 20201025
	//myCanvasRotateAxisStepY=0.0f;

	//added by Mike, 20201025
    myCanvasEyePosX=0.0f;
    myCanvasEyePosY=0.0f;
    myCanvasEyePosZ=3.0f;//0.0f;//3.0f;
    myCanvasCenterPosX=0.0f;
    myCanvasCenterPosY=0.0f;
    //edited by Mike, 20201026
    myCanvasCenterPosZ=1.0f;//1.0f;
/*
	//added by Mike, 20201026
    myCanvasLookAtAngleRad = (myCanvasLookAtAngle) * 3.141593f / 180.0f;
    zAccel = (cos(myCanvasLookAtAngleRad)*myCanvasStepZ);
    xAccel = -(sin(myCanvasLookAtAngleRad)*myCanvasStepX);
*/

/*
 	iRowCountMax=10;
 	iColumnCountMax=10;
*/
	
	//added by Mike, 20201113; edited by Mike, 20201115
/* 	iRowCountMax=10;
 	iColumnCountMax=10;
*/
 	iRowCountMax=20;
 	iColumnCountMax=20;


	fGridSquareWidth = myWindowWidth/iColumnCountMax/100.0;
	fGridSquareHeight = myWindowHeight/iRowCountMax/100.0;

    keyPressCounter=0;
    
    //added by Mike, 20200930
	currentState = GAME_SCREEN; //TO-DO: -update: this
	
	//added by Mike, 20201001
	//edited by Mike, 20201115
	//myRobotShip = new RobotShip;
	myRobotShip = new RobotShip(0.0f,0.0f,0.0f,myWindowWidth,myWindowHeight);

    myRobotShip->setOpenGLCanvas(this);
	
	//added by Mike, 20201013; edited by Mike, 20201014
//	for (i=0; i<MAX_BEAMS; i++) {
	for (int i=0; i<MAX_BEAMS; i++) {
		//edited by Mike, 2020116
//      myBeam[i] = new Beam;
		myBeam[i] = new Beam(0.0f,0.0f,0.0f,myWindowWidth,myWindowHeight);
	}

	//added by Mike, 20201016
	//-------------------------------------------
	numOfAsteroidsLeft=MAX_ASTEROID;

    //init asteroids and set their positions to the four corners 
/*    myAsteroid[0] = new Asteroid(PARENT_STATUS,0.0f,1.0f);//,10,10); //TOP RIGHT
    myAsteroid[1] = new Asteroid(PARENT_STATUS,0.0f,0.0f);//,-10,10); //TOP LEFT
    myAsteroid[2] = new Asteroid(PARENT_STATUS,1.0f,0.0f);//,-10,-10); //BOTTOM LEFT
    myAsteroid[3] = new Asteroid(PARENT_STATUS,1.0f,1.0f);//,10,-10); //BOTTOM RIGHT
*/

/*	//edited by Mike, 20201017
    myAsteroid[0] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT
    myAsteroid[1] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,-10,10); //TOP LEFT
    myAsteroid[2] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,-10,-10); //BOTTOM LEFT
    myAsteroid[3] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,-10); //BOTTOM RIGHT
*/
	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
//    	myAsteroid[i] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i] = new Asteroid(PARENT_STATUS,fGridSquareWidth,0.0f,fGridSquareHeight);//,10,10); //TOP RIGHT
    	myAsteroid[i] = new Asteroid(PARENT_STATUS,fGridSquareWidth,0.0f,fGridSquareHeight,myWindowWidth,myWindowHeight);//TOP RIGHT
	}

	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
    	myAsteroid[i+4] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myWindowWidth,myWindowHeight); //TOP RIGHT		
	}

	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
    	myAsteroid[i+8] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myWindowWidth,myWindowHeight);//TOP RIGHT		
	}

	for (int i=0; i<4; i++) {
		//edited by Mike, 20201113
//    	myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.1f);//,10,10); //TOP RIGHT		
		//edited by Mike, 20201115
//    	myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f);//,10,10); //TOP RIGHT		
    	myAsteroid[i+12] = new Asteroid(PARENT_STATUS,0.1f,0.0f,0.1f,myWindowWidth,myWindowHeight);//TOP RIGHT		
	}

/*	//removed by Mike, 20201016
    for (int i=4; i<12; i++)   
    {
        myAsteroid[i] = new Asteroid(CHILD_STATUS,0,0);
    }
    //group them into 3's
    myAsteroid[0]->attachChild(myAsteroid[4],myAsteroid[5]);
    myAsteroid[1]->attachChild(myAsteroid[6],myAsteroid[7]);
    myAsteroid[2]->attachChild(myAsteroid[8],myAsteroid[9]);
    myAsteroid[3]->attachChild(myAsteroid[10],myAsteroid[11]);

    for (int i=12; i<MAX_ASTEROID; i++)   
    {
        myAsteroid[i] = new Asteroid(GRANDCHILD_STATUS,0,0);
    }
    myAsteroid[4]->attachChild(myAsteroid[12],myAsteroid[13]);
    myAsteroid[5]->attachChild(myAsteroid[14],myAsteroid[15]);
    myAsteroid[6]->attachChild(myAsteroid[16],myAsteroid[17]);
    myAsteroid[7]->attachChild(myAsteroid[18],myAsteroid[19]);
    myAsteroid[8]->attachChild(myAsteroid[20],myAsteroid[21]);
    myAsteroid[9]->attachChild(myAsteroid[22],myAsteroid[23]);
    myAsteroid[10]->attachChild(myAsteroid[24],myAsteroid[25]);
    myAsteroid[11]->attachChild(myAsteroid[26],myAsteroid[27]);
*/
    
    for (int i=0; i<MAX_ASTEROID; i++)   
    {
//      myAsteroid[i] = new Asteroid;
	//removed by Mike, 20201016
//        myAsteroid[i]->setOpenGLCanvas(this);
    }
	//-------------------------------------------

    //added by Mike, 20201011
    setupFont(FONT_TEXTURE);

	//TO-DO: -update: this
    //added by Mike, 20201118
    myLevel = new Level();
    myLevel->setupLevel(FONT_TEXTURE);

	return true;
}

bool OpenGLCanvas::shutdown()
{
/*	//removed by Mike, 20200929
    sound->unload_sound_clip(thrust);
	sound->unload_sound_clip(rotate);
    sound->unload_sound_clip(beam);
    sound->unload_sound_clip(explosion);
	sound->unload_sound_clip(zing);
	sound->unload_sound_clip(title);
	sound->unload_sound_clip(bonus);
	
    sound->sound_stop();
	
    glDeleteTextures(1, &currTextureBackground);
    glDeleteTextures(1, &myTextureObjectFont);
    glDeleteTextures(1, &titleBackground);
    glDeleteTextures(1, &gameBackground);

	//myBackground->Release();
	//delete myBackground;
	
	//releaseFont(myFontListBase);
*/		

	//added by Mike, 20201016
	for (int i=0; i<MAX_ASTEROID; i++)   
    {
        myAsteroid[i]->destroy();
    }
	
	return true;
}

/*	//removed by Mike, 20200929
GLboolean OpenGLCanvas::test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}
*/

/* //removed by Mike, 20200929
//added by Mike, 20200928"RobotShip.h"
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount"RobotShip.h", 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
//Reference: "Beginning OpenGL Game Programming", Chapter 7
//Astle and Kevin Hawkins
//edited by Mike, 2007
void OpenGLCanvas::load_tga(char *filename)
{
    TARGA_HEADER targa;
    FILE *file;
//added by Mike, 20200928
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
    GLubyte *data;
    GLuint i;

    file = fopen(filename, "rb");
    if (file == NULL)
        return;

    // test validity of targa file
    if (fread(&targa, 1, sizeof(targa), file) != sizeof(targa) ||
        targa.id_field_length != 0 || targa.color_map_type != 0 ||
        targa.image_type_code !=
//added by Mike, 20200928
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
//added by Mike, 20200928
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
} 2 || ! test_pow2(targa.width) ||
        ! test_pow2(targa.height) || targa.image_pixel_size != 32 ||
        targa.image_descriptor != 8)
    {
        fclose(file);
        free(data);
        return;
    }

    // read targa file into memory
    data = (GLubyte *) malloc(targa.width * targa.height * 4);
    if (fread(data, targa.width * targa.height * 4, 1, file) != 1)
    {
        fclose(file);
        return;
    }

    // swap texture bytes so that BGRA becomes RGBA
    for (i = 0; i < targa.width * targa.height * 4; i += 4)
    {
        GLbyte swap = data[i];
        data[i] = data[i + 2];
        data[i + 2] = swap;
    }

    // build OpenGL texture
    fclose(file);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, targa.width, targa.height,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
    free(data);
}
*/

/* //removed by Mike, 20200929https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
bool OpenGLCanvas::loadBackground()
{
    // retrieve "unused" texture object
	glGenTextures(1, &titleBackground);

    // select texture 1
    glBindTexture(GL_TEXTURE_2D, titleBackground);//1);

    // create OpenGL texture out of targa file
    //removed by Mike, 20200929
    //TO-DO: -update: this
    //load_tga("textures/title.tga");//background.


    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// retrieve "unused" texture object
	glGenTextures(1, &gameBackground);

    // select texture 1
    glBindTexture(GL_TEXTURE_2D, gameBackground);//1);

    // create OpenGL texture out of targa file
    //removed by Mike, 20200929
    //TO-DO: -update: this
//    load_tga("textures/background.tga");//background.


    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // unselect texture 1
    glBindTexture(GL_TEXTURE_2D, 0);

    currTextureBackground=titleBackground;
}
*/

bool OpenGLCanvas::setupProjection()
{
	/*	//removed by Mike, 20200929
    glViewport(0, 0, myWindowWidth, myWindowHeight); // reset the viewport to new dimensions
	*/
	return true;
}

/*	//removed by Mike, 20200929
void OpenGLCanvas::drawPlane()
{
    //glColor3f(1.0f, 1.0f, 1.0f);//default: white
	glBegin(GL_TRIANGLE_STRIP);
	    //note: In "glTexCoord2f(1.0, 0.0);", if 1.0 is changed to 2.0, the plane is made up of 4 images instead of just 1 whole image 
		glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, -10.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -10.0);
		glTexCoord2f(1.0, 1.0);	glVertex3f(10.0, -10.0, 10.0);
		glTexCoord2f(0.0, 1.0);	glVertex3f(-10.0, -10.0, 10.0);	
	glEnd();
}
*/

void OpenGLCanvas::keyDown(int keyCode)
{
	myKeysDown[keyCode] = TRUE;	
}
void OpenGLCanvas::keyUp(int keyCode)
{
	myKeysDown[keyCode] = FALSE;	
}

void OpenGLCanvas::render()
{     
	//added by Mike, 20201023
	//note: this is to be print-ready in newsletter
	//we use recycled paper
	//edited by Mike, 2020116
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
//   glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // Set background color to white and not opaque

	//added by Mike, 20201012
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    //removed by Mike, 20201015
//    glViewport(0, 0, myWindowWidth, myWindowHeight);		// reset the viewport to new 


    //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//TOP-LEFT origin
	glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maximum
      	);


/*	//removed by Mike, 20201117
    //font 
    // select and enable texture FONT_TEXTURE
	//edited by Mike, 20201012
    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glEnable(GL_TEXTURE_2D);
*/		
    if (currentState==TITLE_SCREEN) {                                    
    }
    else if (currentState==CONTROLS_SCREEN) {
    }
    else if (currentState==GAMEOVER_SCREEN) {
    }
    else if (currentState==HIGHSCORE_SCREEN) {
    }
    else if (currentState==GAME_SCREEN) {
/* //removed by Mike, 20201117
//TO-DO: -update: this
		sprintf(tempText,"USBONG");
		//TO-DO: -update: this to not add 0.1 in y-axis
//	    draw_string(0, 0, tempText);    	
		//edited by Mike, 2020117
//	    draw_string(0, 0.1, tempText);    	
	    draw_string(0, 0.1, tempText);    	

	    glDisable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, 0);
*/

  	//added by Mike, 20201117
    //font 
    /* select and enable texture FONT_TEXTURE */
	//edited by Mike, 20201012
    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glEnable(GL_TEXTURE_2D);

  	//TO-DO: -update: this
	sprintf(tempText,"USBONG");
	//TO-DO: -update: this to not add 0.1 in y-axis
//	    draw_string(0, 0, tempText);    	
	//edited by Mike, 2020117
//	    draw_string(0, 0.1, tempText);    	
    draw_string(0.0f, 0.1f, 0.0f, tempText);    	

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


	//added by Mike, 20201020
	//note: we add these to enable complete drawing of 3D shape with z-axis
	//--------------------------------------------------------
	//removed by Mike, 20201118
//    glEnable(GL_CULL_FACE);

	//removed by Mike, 20201010
	//TO-DO: -reverify: this
	//due to blank output in Font texture
//    glEnable(GL_DEPTH_TEST);
	
	//removed by Mike, 2020117
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//added by Mike, 20201114
//	glDepthFunc(GL_ALWAYS);


	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	//TO-DO: -reverify: these
	// calculate aspect ratio of window
	//gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);	
/*    //edited by Mike, 20201022
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 3.0, // aspect ratio
                   1.0, // near plane
                   100); // far plane
*/

/*	//edited by Mike, 20201114
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 4.0, // aspect ratio
                   0.1, // near plane
                   100); // far plane
*/
    gluPerspective(90.0, // field-of-view angle
                   4.0 / 3.0, // aspect ratio
                   0.1, // near plane
                   100); // far plane

/* //removed by Mike, 20201118
	//TO-DO: -reverify: these
	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix
*/

/*
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 0.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
/*
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              1.0, 0.0, 0.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
/*	UFO Catcher View; Z as up
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 0.0, 1.0); // up-direction
*/
/*	UFO Catcher View; Y as up
	//reverify: roboship cube
    gluLookAt(0.0, -1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/

	//edited by Mike, 20201023
/*
    gluLookAt(0.0, 1.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/

/*	//edited by Mike, 20201025
    gluLookAt(myCanvasEyePosX, 0.0, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
//              1.0, 1.0, 0.0); // up-direction //floor head down
*/
/*	//edited by Mike, 20201115
    gluLookAt(myCanvasEyePosX, myCanvasEyePosY, myCanvasEyePosZ, // eye position 0.0, 0.0, 3.0
              myCanvasCenterPosX, myCanvasCenterPosY, myCanvasCenterPosZ, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
    gluLookAt(myCanvasEyePosX, myCanvasEyePosY, myCanvasEyePosZ, // eye position 0.0, 0.0, 3.0
              myCanvasCenterPosX, myCanvasCenterPosY, myCanvasCenterPosZ, // look-at point
              0.0, 1.0, 0.0); // up-direction

/*
    gluLookAt(0.0, 0.5, 3.0, // eye position 0.0, 0.0, 3.0
              0.0, 0.0, 1.0, // look-at point
              0.0, 1.0, 0.0); // up-direction
*/
	//--------------------------------------------------------

	//note: reference point/origin at center; not top-left
	//added by Mike, 20201115
	glRotatef(45, 1.0f, 0.0f, 0.0f);
	glRotatef(30, 0.0f, 1.0f, 0.0f);
    glScalef(0.3f, 0.3f, 0.3f);

//    glTranslatef(-1.0f, -1.0f, 0.0f);

	//edited by Mike, 2021022
//    glTranslatef(-1.0f, -1.0f, 0.0f);
//    glTranslatef(-3.0f, -1.0f, 0.0f);
//    glTranslatef(-3.2f, 0.0f, 0.0f);
	//edited by Mike, 20201023
//    glTranslatef(-3.2f, 0.0f, -3.2f);
    glTranslatef(myCanvasPosX, myCanvasPosY, myCanvasPosZ);
  
    //added by Mike, 2020116; edited by Mike, 20201116
   	//wrap the world 
/*
//           		if (myXPos <= 0.0f) myXPos = 20-myWidth/8; //if left side
	if (myCanvasPosX <= 0.0f) myCanvasPosX = myWindowWidth/100;//-myWidth/8; //if left side
	else if (myCanvasPosX >= myWindowWidth/100) myCanvasPosX = 0.0f;//+myWidth/8; //if right side

	if (myCanvasPosZ >= myWindowHeight/100) myCanvasPosZ = 0.0f;//+myHeight/8; //if bottom side
	//edited by Mike, 20201116
//           		else if (myZPos <= 0.0f) myZPos = 20-myHeight/8; //if top side
	else if (myCanvasPosZ <= 0.0f) myCanvasPosZ = myWindowHeight/100;//-myHeight/8; //if top side
*/
	//note: negative value
	if (myRobotShip->getX() <= 0.0f) myCanvasPosX = 0.0f-myWindowWidth/100+myRobotShip->getWidth()/8;//-myWidth/8; //if left side
	else if (myRobotShip->getX() >= myWindowWidth/100) myCanvasPosX = 0.0f+myRobotShip->getWidth()/8;//+myWidth/8; //if right side

	if (myRobotShip->getZ() >= myWindowHeight/100) myCanvasPosZ = 0.0f+myRobotShip->getHeight()/8; //if bottom side
	//note: negative value
	else if (myRobotShip->getZ() <= 0.0f) myCanvasPosZ = 0.0f-myWindowHeight/100+myRobotShip->getHeight()/8;//-myHeight/8; //if top side
   
    //added by Mike, 20201024
//    glTranslatef(3.2f, 1.0f, 3.2f);    
//    glTranslatef(0.0f, 0.0f, 3.2f);
//    glTranslatef(3.2f, 0.0f, 6.4f);
	//removed by Mike, 20201025
//	glRotatef(myCanvasRotateAxisStepY, 0.0f, 1.0f, 0.0f);
	//added by Mike, 20201026; removed by Mike, 20201026
//	glRotatef(myCanvasLookAtAngle, 0.0f, 1.0f, 0.0f);
    

/*
    	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
    	glLoadIdentity();						// reset projection matrix
    	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
    	// load the identity matrix (clear to default position and orientation)
    	glLoadIdentity();  
*/
		
    	//added by Mike, 20200930
    	drawGridWithZAxis();
			    
    		//added by Mike, 20201011

		//TO-DO: -update: this
/*
        currTextureBackground=gameBackground;

        sprintf(tempText,"1P \n       %d", score);
        draw_string(-200, 130, tempText);
    
    	sprintf(tempText,"HIGH-SCORE\n  %d",highScore);
        draw_string(90, 130, tempText);
    
    	sprintf(tempText,"REST %d", rest);
        draw_string(100, -150, tempText);

        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        //for the rest of the objects in the world
    	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
    	glLoadIdentity();						// reset projection matrix
        gluPerspective(90.0, // field-of-view angle
                       4.0 / 3.0, // aspect ratio
                       1.0, // near plane
                       myWindowWidth); //or myWindowHeight will do, since they are equal
                       //100); // far plane
    
    	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
    	// load the identity matrix (clear to default position and orientation)
    	glLoadIdentity();  
        //note: this is assuming that myWindowWidth and myWindowHeight are equal
        gluLookAt(0.0, 5.0, myWindowWidth/2, // eye position 0.0, 0.0, 3.0
                  0.0, 0.0, 0.0, // look-at point
                  0.0, 1.0, 0.0); // up-direction
*/

		//added by Mike, 20201001
    	glPushMatrix();		
    		//added by Mike, 202013; edited by Mike, 20201014
//            for(i=0; i<MAX_BEAMS; i++) {
            for(int i=0; i<MAX_BEAMS; i++) {
              if (myBeam[i]->isActive()) {
                myBeam[i]->draw();
			  }
            }
        glPopMatrix();       
		
		//edited by Mike, 20201016
    	glPushMatrix();		        
            myRobotShip->drawRobotShip();			
        glPopMatrix();       

		//edited by Mike, 20201016
    	glPushMatrix();		                
			//added by Mike, 20201016
            for(int i=0; i<MAX_ASTEROID; i++) {
              //if (myBeam[i]->isActive())
                myAsteroid[i]->draw();
            }
    	glPopMatrix();		

     }
}

//edited by Mike, 20201022
/* //previous drawGridWithZAxis()
//added by Mike, 20201020
void OpenGLCanvas::drawGridWithZAxis() {
//	//removed by Mike, 20201020
//     //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
//	 glMatrixMode(GL_PROJECTION);
//	 glLoadIdentity();

	 //TO-DO: -add: Z plane grid
	
	 //draw grid
	 //edited by Mike, 20201015 	 
 	 //TO-DO: -update: iRowCountMax
// 	 int iRowCountMax=10;
 	 int iRowCountMax=20;
 	 //TO-DO: -update: iColumnCountMax
// 	 int iColumnCountMax=10;
 	 int iColumnCountMax=20;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
   	//edited by Mike, 20201002
 	 for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
			//edited by Mike, 20201022
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(1.0f, 0.1f*iRowCount);
      		glVertex2f(0.1f*iRowCountMax, 0.1f*iRowCount);
      		
   		glEnd();   		   	  
	 }

   //columns
   	//edited by Mike, 20201015   	
 	 for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(0.1f*iColumnCount, 1.0f);
      		glVertex2f(0.1f*iColumnCount, 0.1f*iColumnCountMax);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}
*/
//added by Mike, 20201020
void OpenGLCanvas::drawGridWithZAxis() {
/*	//removed by Mike, 20201020
     //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
*/

	 //TO-DO: -add: Z plane grid
	
	 //draw grid
	 //edited by Mike, 20201015 	 
 	 //TO-DO: -update: iRowCountMax
 	 //edited by Mike, 20201022
 	 //removed by Mike, 20201113
// 	 int iRowCountMax=10;
// 	 int iRowCountMax=20;

 	 //TO-DO: -update: iColumnCountMax
 	 //edited by Mike, 20201022
 	 //removed by Mike, 20201113
// 	 int iColumnCountMax=10;
// 	 int iColumnCountMax=20;

	//added by Mike, 20201022
	//example: 640/10 = 64; 64/100 = .64
	//half the window
	//example: 640/2 = 320; 320/10 = 32; 32/100 = .32
/*
	float fColumnSquareWidth = myWindowWidth/2/iRowCountMax/100.0;
	float fRowSquareHeight = myWindowHeight/2/iColumnCountMax/100.0;
*/
	//edited by Mike, 20201022
/*	//half window width and height
	float fSquareWidth = myWindowWidth/2/iColumnCountMax/100.0;
	float fGridSquareHeight = myWindowHeight/2/iRowCountMax/100.0;
*/

	//removed by Mike, 20201113
//	float fSquareWidth = myWindowWidth/iColumnCountMax/100.0;
//	float fGridSquareHeight = myWindowHeight/iRowCountMax/100.0;

/*	//removed by Mike, 20201119
   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
   	//edited by Mike, 20201002
 	 for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
			//added by Mike, 20201023
			//floor face
			//with Z-axis
      		glVertex3f(0.0f, 0.0f, fGridSquareHeight*iRowCount);    // x, z
      		glVertex3f(fGridSquareWidth*iRowCountMax, 0.0f, fGridSquareHeight*iRowCount);      		
   		glEnd();   		   	  
	 }

   //columns
   	//edited by Mike, 20201015   	
 	 for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
			//added by Mike, 20201022			
			//with Z-axis
      		glVertex3f(fGridSquareWidth*iColumnCount, 0.0f, 0.0f);    // y, z
      		glVertex3f(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iColumnCountMax);

   		glEnd();   		   	  
	 }
*/

  	//added by Mike, 20201118
  	//LEVEL TEXTURE
    /* select and enable texture FONT_TEXTURE */
	//edited by Mike, 20201012
    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
    glEnable(GL_TEXTURE_2D);

	//TO-DO: -fix: column's right border 
	//column : z-axis
	//TO-DO: -fix: row's bottom border 
	//column : x-axis
	
	//note: add: randomly tile with texture
	
  	//edited by Mike, 20201119
	//TO-DO: -update: this
	//note: D = "Door"
//	sprintf(tempText,"D");
//	myLevel->draw_level(0.0f, 0.0f, 0.0f, tempText);    	
 	//columns
   	//edited by Mike, 20201015   	
    //rows   
	sprintf(tempText,"D");
 	for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {	
	 	for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {		
	    	myLevel->draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
		}
	}

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

   
   glFlush();  // Render now
}

//added by Mike, 20200930
void OpenGLCanvas::drawGrid() {
	//removed by Mike, 20201012
/*   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
*/
 
     //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();

	 //TOP-LEFT origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maximum
      	);

	//edited by Mike, 20201016
	//added by Mike, 20201002

/*	//note: set these to be isometric view
    glRotatef(40, 0.0f, 0.0f, 0.2f);
//    glTranslatef(0.45f, -0.15f, 0.0f); //10x10 grid
    glTranslatef(0.45f, -0.20f, 0.0f); //20x20 grid
//    glScalef(0.5f, 0.5f, 0.5f); //10x10 grid
    glScalef(0.3f, 0.3f, 0.3f); //20x20 grid
*/

/*
	//edited by Mike, 20201018
	//+increased: size of grid from 10x10 to 20x20
	//non-isometric view
	//edited by Mike, 20201018
//    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.2f, 0.2f, 0.0f); //20x20 grid
    glScalef(0.3f, 0.3f, 0.3f);
*/

/*
	//added by Mike, 20201018
	//TO-DO: -update: this
	//first-person view
    glRotatef(90.0f, 1.0f, 0.0f, 0.1f); //roll clock-wise
	//added by Mike, 20201019
	//note decrease, i.e. increase negatively, z value, to move forward
    glTranslatef(0.0f, -1.0f, -0.8f); //20x20 grid
*/

/*
	//note: set these to be isometric view
//    glRotatef(30, 0.0f, 0.0f, 0.2f);
//    glRotatef(30, 0.0f, 0.0f, 1.0f);
    glRotatef(60, 1.0f, 0.0f, 0.0f);

//    glTranslatef(0.45f, -0.15f, 0.0f); //10x10 grid
    glTranslatef(0.45f, -0.20f, 0.0f); //20x20 grid
//    glScalef(0.5f, 0.5f, 0.5f); //10x10 grid
    glScalef(0.3f, 0.3f, 0.3f); //20x20 grid
*/

//    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
//	glRotatef(15.0, 1.0, 0.0, 0.0);

//	glRotatef(60.0f, 0.0, 0.0, 1.0);
//	glRotatef(30.0f, 1.0, 0.0, 0.0);
  	glRotatef(60.0f, 1.0, 0.0, 0.0);

    glTranslatef(0.2f, 0.0f, 0.0f); //20x20 grid
      
//    glTranslatef(0.2f, 0.2f, 0.0f); //20x20 grid
//    glScalef(0.3f, 0.3f, 0.3f);


//    glTranslatef(0.0f, 0.0f, 1.0f); //20x20 grid

	//edited by Mike, 20201019
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//    glTranslatef(0.2f, -0.5f, -0.5f); //20x20 grid
//    glScalef(0.3f, 0.3f, 0.3f);


/*
//    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
//    glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

//    glTranslatef(0.2f, -0.5f, -0.5f); //20x20 grid
//    glTranslatef(0.0f, -0.5f, -0.9f); //20x20 grid
//    glTranslatef(0.0f, -0.7f, -0.9f); //20x20 grid
//    glTranslatef(0.0f, -1.0f, -0.5f); //20x20 grid
    glTranslatef(0.0f, -1.0f, -0.8f); //20x20 grid
*/

//    glScalef(0.3f, 0.3f, 0.3f);


/*
	//use these to verify grid
    glTranslatef(0.1f, 0.1f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
*/	
	 //draw grid
	 //edited by Mike, 20201015 	 
 	 //TO-DO: -update: iRowCountMax
// 	 int iRowCountMax=10;
 	 int iRowCountMax=20;
 	 //TO-DO: -update: iColumnCountMax
// 	 int iColumnCountMax=10;
 	 int iColumnCountMax=20;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
   	//edited by Mike, 20201002
 	 for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(1.0f, 0.1f*iRowCount);
      		glVertex2f(0.1f*iRowCountMax, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
   	//edited by Mike, 20201015   	
 	 for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//edited by Mike, 20201015
//      		glVertex2f(0.1f*iColumnCount, 1.0f);
      		glVertex2f(0.1f*iColumnCount, 0.1f*iColumnCountMax);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}

void OpenGLCanvas::update()
{           
    if (currentState==GAME_SCREEN) {
/*		//removed by Mike, 20201016
    	//added by Mike, 20201016
        if(numOfAsteroidsLeft<=0) {
            resetDynamicObjects();
        }
*/
    	
    	//added by Mike, 20201001
    	myRobotShip->update(1); //dt
		
		//added by Mike, 20201013
/*    	int a;
*/
		//edited by Mike, 20201014
//        for(i=0; i<MAX_BEAMS; i++) {
        for(int i=0; i<MAX_BEAMS; i++) {
          if ( (myRobotShip->getState()!=ROBOTSHIP_INITIALIZING_STATE) &&
               (myBeam[i]->isActive()) ){
            myBeam[i]->update(1);

            //check collisions
            //myBeam[i]->collideWith(myEnemy);
			
			//added by Mike, 20201016
            for(int a=0; a<MAX_ASTEROID; a++) {
              myBeam[i]->collideWith(myAsteroid[a]);
			}              
          }
		}

		//added by Mike, 20201016
        for(int i=0; i<MAX_ASTEROID; i++) {
          //if (myBeam[i]->isActive())
            myAsteroid[i]->update(1);
            //removed by Mike, 20201016
//            myAsteroid[i]->collideWith(myRobotShip);        
        }

       	//process input
       	//TO-DO: -update: this
       	//TO-DO: -verify: gamepad
       	//edited by Mike, 20201013
    	if(myKeysDown[KEY_UP] == TRUE)
//    	if(myKeysDown[KEY_W] == TRUE)
    	{
    		//added by Mike, 20201001
          	//myRobotShip->move(KEY_UP);

          	//edited by Mike, 20201115
          	myRobotShip->move(KEY_W);
			//removed by Mike, 20201026
/*			  myCanvasPosZ+=myCanvasStepZ;
*/

			//move forward
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ-=sin(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX-=cos(myCanvasLookAtAngle)*myCanvasStepX;


			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
       	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_DOWN] == TRUE)
    	//edited by Mike, 20201014
    	if(myKeysDown[KEY_S] == TRUE)
//    	else if(myKeysDown[KEY_S] == TRUE)
    	{
    		//edited by Mike, 20201115
            myRobotShip->move(KEY_DOWN);
/*			//removed by Mike, 20201026
			myCanvasPosZ-=myCanvasStepZ;
*/
			//move backward
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ+=sin(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX+=cos(myCanvasLookAtAngle)*myCanvasStepX;

    	}
       	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_RIGHT] == TRUE)
    	//edited by Mike, 20201014
    	//else if(myKeysDown[KEY_D] == TRUE)
//    	if(myKeysDown[KEY_D] == TRUE)
    	if(myKeysDown[KEY_RIGHT] == TRUE)
    	{
    		//added by Mike, 20201001
    		//edited by Mike, 20201115
            myRobotShip->move(KEY_RIGHT);
/*			//removed by Mike, 20201026
			myCanvasPosX+=-myCanvasStepX;
*/

			//move right
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ-=cos(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX+=sin(myCanvasLookAtAngle)*myCanvasStepX;

			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
       	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_LEFT] == TRUE)
    	//edited by Mike, 20201014
    	//else if(myKeysDown[KEY_A] == TRUE)
    	if(myKeysDown[KEY_A] == TRUE)
    	{
    		//added by Mike, 20201001
    		//edited by Mike, 20201115
            myRobotShip->move(KEY_LEFT);

			//removed by Mike, 20201026
/*			myCanvasPosX+=myCanvasStepX;
*/			
			//move left
			//Reference: https://community.khronos.org/t/moving-an-object-with-respect-to-the-camera/40968;
			//last accessed: 20201026
			//answer by: Bob, 200002
			myCanvasPosZ+=cos(myCanvasLookAtAngle)*myCanvasStepZ;
			myCanvasPosX-=sin(myCanvasLookAtAngle)*myCanvasStepX;

			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
    	
    	
    	//TO-DO: -update: to execute diagonal beams
		//TO-DO: -reverify: rotation angle
    	
    	//edited by Mike, 20201013
    	//else if(myKeysDown[KEY_SPACE] == TRUE)
        //Reference: 
        //https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
        //last accessed: 20201013    	
        //edited by Mike, 20201015
//    	else if(myKeysDown[KEY_J] == TRUE)
    	if(myKeysDown[KEY_J] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;

			//added by Mike, 20201023
			//move down
			//myCanvasPosY+=myCanvasStepY;
			//turn left
			//edited by Mike, 20201024
/*			myCanvasEyePosX+=myCanvasEyeStepX;
			myCanvasPosX+=myCanvasStepX;
*/
			//TO-DO: -add: in turn right

/*			//removed by Mike, 20201115; due to top view plus isometric view			
			//Reference:
			//https://stackoverflow.com/questions/29452725/how-can-i-make-my-opengl-camera-turn-360-degrees;
			//answer by: Chris DuPuis, 20150405T0235
			myCanvasLookAtAngle-=0.1f;
			myCanvasCenterPosZ = myCanvasEyePosZ + sin(myCanvasLookAtAngle);
			myCanvasCenterPosX = myCanvasEyePosX + cos(myCanvasLookAtAngle);

			//added by Mike, 20201026
            if (myCanvasLookAtAngle>360.0f) {
              myCanvasLookAtAngle-=360.0f;
		    }
            else if (myCanvasLookAtAngle<-360.0f) {
              myCanvasLookAtAngle+=360.0f;
		    }
*/
						
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				  //edited by Mike, 20201013
//                myBeam[i]->move(myRobotShip->getRotationAngle(), myRobotShip->getXYZPos());
				
				//LEFT
				rotationAngle=90;
                myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}
    	//edited by Mike, 20201015
//    	else if(myKeysDown[KEY_L] == TRUE)
    	if(myKeysDown[KEY_L] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;


			//added by Mike, 20201023
			//move up
			//myCanvasPosY-=myCanvasStepY;
			//turn right
/*			//removed by Mike, 20201025
			myCanvasEyePosX-=myCanvasEyeStepX;
			myCanvasPosX-=myCanvasStepX;
*/

/*			//removed by Mike, 20201115; due to top view plus isometric view
			//added by Mike, 20201026
			//Reference:
			//https://stackoverflow.com/questions/29452725/how-can-i-make-my-opengl-camera-turn-360-degrees;
			//answer by: Chris DuPuis, 20150405T0235
			myCanvasLookAtAngle+=0.1f;
			myCanvasCenterPosZ = myCanvasEyePosZ + sin(myCanvasLookAtAngle);
			myCanvasCenterPosX = myCanvasEyePosX + cos(myCanvasLookAtAngle);

			//added by Mike, 20201026
            if (myCanvasLookAtAngle>360) {
              myCanvasLookAtAngle-=360;
		    }
            else if (myCanvasLookAtAngle<-360) {
              myCanvasLookAtAngle+=360;
		    }
*/			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				  //edited by Mike, 20201013
//                myBeam[i]->move(myRobotShip->getRotationAngle(), myRobotShip->getXYZPos());
				
				//RIGHT
				rotationAngle=-90;
                myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}
		//edited by Mike, 20201015
//    	else if(myKeysDown[KEY_I] == TRUE)
    	if(myKeysDown[KEY_I] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;

//            myRobotShip->move(KEY_LEFT);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				  //edited by Mike, 20201013
//                myBeam[i]->move(myRobotShip->getRotationAngle(), myRobotShip->getXYZPos());
				
				//UP
				rotationAngle=180;
                myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}
		//edited by Mike, 20201015
//    	else if(myKeysDown[KEY_K] == TRUE)
    	if(myKeysDown[KEY_K] == TRUE)
    	{
			//edited by Mike, 20201013
			static int i = 0;

//            myRobotShip->move(KEY_LEFT);
			
            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
				  //edited by Mike, 20201013
//                myBeam[i]->move(myRobotShip->getRotationAngle(), myRobotShip->getXYZPos());
				
				//DOWN
				rotationAngle=0;
                myBeam[i]->move(rotationAngle, myRobotShip->getXYZPos());

//		        sound->play_sound_clip(beam);
                return;
              }
            }			
    	}
     }
     else if (currentState==TITLE_SCREEN)
     {
     }
     else if (currentState==CONTROLS_SCREEN)
     {
     }
     else if (currentState==HIGHSCORE_SCREEN)
     {
     }
     else if (currentState==GAMEOVER_SCREEN)
     {
/*		//removed by Mike, 20200929		 
		if(myKeysDown[KEY_SPACE] == TRUE)
		{
		  gameReset();
		}
*/		
     }
}

void OpenGLCanvas::gameReset(){
/*	//removed by Mike, 20200929
    score=0;
    scoreBeforeBonus=0;
    myRobotShip->reset();
    rest=MAX_LIFE;

    resetDynamicObjects();
    changeState(GAME_SCREEN);
*/	
}

void OpenGLCanvas::resetDynamicObjects(){
/*	//removed by Mike, 20200929
    myAsteroid[0]->reset(15,15); //TOP RIGHT
    myAsteroid[1]->reset(-15,15); //TOP LEFT
    myAsteroid[2]->reset(-15,-15); //BOTTOM LEFT
    myAsteroid[3]->reset(15,-15); //BOTTOM RIGHT

    for (i=4; i<12; i++) {   
      myAsteroid[i]->changeState(CHILD_STATUS);
      myAsteroid[i]->setCollidable(false);
    }
    for (i=12; i<MAX_ASTEROID; i++) {   
      myAsteroid[i]->changeState(GRANDCHILD_STATUS);
      myAsteroid[i]->setCollidable(false);
    }
    //for (i=0; i<MAX_ASTEROID; i++)   
    numOfAsteroidsLeft=MAX_ASTEROID;
    
    for (i=0; i<MAX_BEAMS; i++)
      myBeam[i]->changeState(HIDDEN_STATE);
*/  
}

void OpenGLCanvas::addScore(int s)
{
/*	//removed by Mike, 20200929
     score+=s;
     scoreBeforeBonus+=s;
     if (scoreBeforeBonus>=REQUIRED_POINTS_FOR_BONUS) {
       sound->play_sound_clip(bonus);
       rest++;
       scoreBeforeBonus-=REQUIRED_POINTS_FOR_BONUS;
     }
     numOfAsteroidsLeft--;
*/	 
}
void OpenGLCanvas::loseLife()
{
/*	//removed by Mike, 20200929
     rest-=1;
     if (rest==0) {
        if(score>highScore)
        {
          //save score in a text file
          highScore=score;
       	  out = fopen(outfile, "w");
          fprintf(out,"%d",highScore);
          fclose(out);
          changeState(HIGHSCORE_SCREEN);
          sound->play_sound_clip(title);
        }     
        else changeState(GAMEOVER_SCREEN);
     }
*/
}
void OpenGLCanvas::changeState(int s)
{
  currentState=s;                  
}

