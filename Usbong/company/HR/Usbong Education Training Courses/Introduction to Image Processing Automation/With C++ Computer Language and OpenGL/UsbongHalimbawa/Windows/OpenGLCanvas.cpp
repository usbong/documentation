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
 * @date updated: 20200930
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

//#include "Sound.h"

//#include "DynamicObject.h"

//#include "glfont.h"

int i;

enum Keys
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	KEY_ENTER
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
    myWindowWidth=640;
    myWindowHeight=640;

    keyPressCounter=0;
    
    //added by Mike, 20200930
		currentState = GAME_SCREEN; //TO-DO: -update: this
	
	//removed by Mike, 20200929
	//TO-DO: -add: these
/*	
	myRobotShip = new RobotShip;
    myRobotShip->setOpenGLCanvas(this);
*/
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
    //font 
    /* select and enable texture FONT_TEXTURE */
	//removed by Mike, 20200929
	//TO-DO: -update: this
/*    glBindTexture(GL_TEXTURE_2D, FONT_TEXTURE);
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
    	//added by Mike, 20200930
    	drawGrid();
    
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

		//removed by Mike, 20200929
/*		//TO-DO: -add: these    
    	glPushMatrix();		
            myRobotShip->drawRobotShip();
    	glPopMatrix();		
*/    	
     }
}


//added by Mike, 20200930
void OpenGLCanvas::drawGrid() {
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

void OpenGLCanvas::update()
{           
    if (currentState==GAME_SCREEN) {
		//removed by Mike, 20200929
		//TO-DO: -add: this
/*    	myRobotShip->update(1); //dt
*/
       	//process input
    	if(myKeysDown[KEY_UP] == TRUE)
    	{
			//removed by Mike, 20200929
			//TO-DO: -add: this
/*            myRobotShip->move(KEY_UP);
*/
			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
    	else if(myKeysDown[KEY_DOWN] == TRUE)
    	{
			//removed by Mike, 20200929
			//TO-DO: -add: this
/*            myRobotShip->move(KEY_DOWN);
*/
    	}
    	else if(myKeysDown[KEY_RIGHT] == TRUE)
    	{
			//removed by Mike, 20200929
			//TO-DO: -add: this
/*            myRobotShip->move(KEY_RIGHT);
*/
			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
    	else if(myKeysDown[KEY_LEFT] == TRUE)
    	{
			//removed by Mike, 20200929
			//TO-DO: -add: this
/*            myRobotShip->move(KEY_LEFT);
*/
			//removed by Mike, 20200929
//			sound->play_sound_clip(thrust);
    	}
    	else if(myKeysDown[KEY_SPACE] == TRUE)
    	{
/*			//removed by Mike, 20200929
			static int i = 0;

            for(i=0; i<MAX_BEAMS; i++) {
              if (!myBeam[i]->isActive()) {
                myBeam[i]->move(myRobotShip->getRotationAngle(), myRobotShip->getXYZPos());
		        sound->play_sound_clip(beam);
                return;
              }
            }
*/			
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

