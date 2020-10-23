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
 * @date created: 20200930
 * @date updated: 20201017
 *
 * Reference: 
 * 1) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 * 
 */
//TO-DO: -update: this

#include <stdio.h>
#include <math.h>

#include <gl/gl.h>
#include <gl/glu.h>

#include "RobotShip.h"
/* //TO-DO: -add: these
#include "PolygonUtils.h"
#include "ModelPool.h"
*/

#include <string.h>
#include <windows.h> //Windows Machine

//#include "ModelPool.h"

//edited by Mike, 20201014
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

//object: Cube.005_0
//body
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

//TO-DO: -put: in MyDynamicObject
GLboolean RobotShip::test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}

//TO-DO: -put: in MyDynamicObject
//Note: [Warning] deprecated conversion from string constant to 'char*' [-Wwrite-strings]
void RobotShip::load_tga(char *filename)
{
    TARGA_HEADER targa;
    FILE *file;
    GLubyte *data;
    GLuint i;

    file = fopen(filename, "rb");
    if (file == NULL)
        return;

    /* test validity of targa file */
    if (fread(&targa, 1, sizeof(targa), file) != sizeof(targa) ||
        targa.id_field_length != 0 || targa.color_map_type != 0 ||
        targa.image_type_code != 2 || ! test_pow2(targa.width) ||
        ! test_pow2(targa.height) || targa.image_pixel_size != 32 ||
        targa.image_descriptor != 8)
    {
        fclose(file);
        free(data);
        return;
    }

    /* read targa file into memory */
    data = (GLubyte *) malloc(targa.width * targa.height * 4);
    if (fread(data, targa.width * targa.height * 4, 1, file) != 1)
    {
        fclose(file);
        return;
    }

    /* swap texture bytes so that BGRA becomes RGBA */
    for (i = 0; i < targa.width * targa.height * 4; i += 4)
    {
        GLbyte swap = data[i];
        data[i] = data[i + 2];
        data[i + 2] = swap;
    }

    /* build OpenGL texture */
    fclose(file);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, targa.width, targa.height,
                      GL_RGBA, GL_UNSIGNED_BYTE, data);
    free(data);
}

//TO-DO: -update: this
void RobotShip::setup()
{
    GLuint i, j;
	
	/* select and enable texture 1 */
    glBindTexture(GL_TEXTURE_2D, 1);
	
	/* create OpenGL texture out of targa file */
    load_tga("textures/body/halimbawa.body.tga");
	
    /* set texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//...
	
	/* select and enable texture 5 */
    glBindTexture(GL_TEXTURE_2D, 5);
	
	/* create OpenGL texture out of targa file */
    load_tga("textures/cockpit/halimbawa.cockpit.tga");
	
    /* set texture parameters */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	//...
	
	/* select and enable texture 8 */
    glBindTexture(GL_TEXTURE_2D, 8);
	
	/* create OpenGL texture out of targa file */
    load_tga("textures/wings/halimbawa.wings.tga");
	
/*	
	//EXPLOSION/ DEATH ANIMATION
	    // retrieve "unused" texture object
	glGenTextures(1, &myDeathAnimationImg1);

    glBindTexture(GL_TEXTURE_2D, myDeathAnimationImg1);

    load_tga("textures/explosion/explosion1.tga");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	    // retrieve "unused" texture object
	glGenTextures(1, &myDeathAnimationImg2);

    glBindTexture(GL_TEXTURE_2D, myDeathAnimationImg2);

    load_tga("textures/explosion/explosion2.tga");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &myDeathAnimationImg3);

    glBindTexture(GL_TEXTURE_2D, myDeathAnimationImg3);

    load_tga("textures/explosion/explosion3.tga");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	    // retrieve "unused" texture object
	glGenTextures(1, &myDeathAnimationImg4);

    glBindTexture(GL_TEXTURE_2D, myDeathAnimationImg4);

    load_tga("textures/explosion/explosion4.tga");

	    // retrieve "unused" texture object
	glGenTextures(1, &myDeathAnimationImg5);

    glBindTexture(GL_TEXTURE_2D, myDeathAnimationImg5);

    load_tga("textures/explosion/explosion5.tga");

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
*/	
	/* unselect and disable texture 1 */
    glBindTexture(GL_TEXTURE_2D, 0);
	
	/* setup alpha blending */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

//added by Mike, 20201001
//TO-DO: -add: this in ModelPool.cpp
void RobotShip::drawModelRobotShip() {
/*	//edited by Mike, 20201019
	//added by Mike, 20201002
	//to make anchor/origin/reference point start at top-left
    glTranslatef(0.0f, 0.1f, 0.0f);   
	
	//Reference: https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html;
	//last accessed: 20200928 
   //note: 0.5f = half of the window width or height
   // Draw a Red 1x1 Square centered at origin
   //TO-DO: -update: this due to output is 1 x 2 box, width x height
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
//    //edited by Mike, 20201001  
//	  glVertex2f(-0.1f, -0.1f);    // x, y
//      glVertex2f( 0.1f, -0.1f);
//      glVertex2f( 0.1f,  0.1f);
//      glVertex2f(-0.1f,  0.1f);
      
	  //1x1 box
	  glVertex2f(0.0f, 0.0f);    // x, y
      glVertex2f( 0.0f, -0.1f);
      glVertex2f( 0.1f,  -0.1f);
      glVertex2f(0.1f,  0.0f);
   glEnd();    
*/   

/*
	glRotatef(15.0, 1.0, 0.0, 0.0);
	glRotatef(30.0f, 0.0, 1.0, 0.0);
	glScalef(0.75, 0.75, 0.75);
*/

	//removed by Mike, 20201020
/*	glRotatef(-10.0, 1.0, 0.0, 0.0);
	glRotatef(35.0f, 0.0, 1.0, 0.0);
*/
	
	//added by Mike, 20201023
	//set square face with no color fill 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	    glColor3f(1.0f, 0.0f, 0.0f); // Red
	
		//edited by Mike, 20201023
	//	drawCube();
		drawCube(myWidth); //myWidth = myHeight

	//added by Mike, 20201023
	//set square face with color fill 	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

//edited by Mike, 20201001
//RobotShip::RobotShip(): MyDynamicObject(0,0,300)
RobotShip::RobotShip(): MyDynamicObject(0,0,0)
{ 
    //edited by Mike, 20201001
	//currentState=IN_TITLE_STATE;//MOVING_STATE;
	currentState=MOVING_STATE;

//    myXPos=0.0;
//    myYPos=0.0;
    //myYPos=300.0;
//    myZPos=300.0;
/*    
    stepX=0.01;
    stepY=0.01;
    stepZ=0.01;
*/    
/*	//edited by Mike, 20201023
	//added by Mike, 20201001
    stepX=0.03;
    stepY=0.03;
*/
    stepX=0.1;
    stepY=0.1;

    invincibleCounter=0;
    currentDeathFrame=0;

	//edited by Mike, 20201001
/*  myWidth=2.0f;//1.5;
    myHeight=2.0f;//1.5;
*/    
/*	//edited by Mike, 20201023
    myWidth=0.1f;
    myHeight=0.1f;
*/
/*
    myWidth=1.0f;
    myHeight=1.0f;
*/
    myWidth=0.5f;
    myHeight=0.5f;

	//added by Mike, 20201001; edited again by Mike, 20201001
	//note: initial position, top-left
/*    myXPos=0.0f;
    myYPos=0+myHeight;//0.1f;
*/
	//note: position: 3,3; width, height; count starts at 0
    myXPos=0.0f+myWidth*3;
    myYPos=0.0f+myHeight*3;

//    myWidthX=0.5;

    rotationAngle=0.0f;//360.0f;//90.0;
    rotationStep=10.0;//1.0f;    
    thrust=0.0f;
    thrustMax=0.8f;
    xVel;
    yVel;
    //edited by Mike, 20201001
    maxXVel=0.04f;//1.0f;
    maxYVel=0.04f;//1.0f;

    //boundary = 8.0f;

    tricount = 120;
    isMovingForward = 0;
    
    //init default values
    //previousFacingState=FACING_UP;
    //currentFacingState=FACING_UP;
	
	//loadTexture(myBodyTexture, "bodyTexture.tga", &myBodyTextureObject);
	//loadTexture(myHeadTexture, "headTexture.tga", &myHeadTextureObject);
	//removed by Mike, 20201001
//	setup();
	
    setCollidable(true);
}

RobotShip::~RobotShip()
{
}

float* RobotShip::getXYZPos()
{
      //float myXYZ[3];
      float* myXYZ;
      myXYZ = (float*) malloc(3*sizeof(float));
      myXYZ[0]=myXPos;
      myXYZ[1]=myYPos;
      myXYZ[2]=myZPos;
      
      return myXYZ;
}

//TO-DO: -update: this
void RobotShip::drawRobotShip()
{

	//removed by Mike, 20201001
//    glPushMatrix();  
/*
	//added by Mike, 20201001
    //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//TOP-LEFT origin
	glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
*/	
	//added by Mike, 20201001
	//edited by Mike, 20201020
	//TO-DO: -update: this
//    glTranslatef(myXPos, myYPos, myZPos);
    glTranslatef(myXPos, myZPos, myYPos);    

	//added by Mike, 20201001
	//TO-DO: -update: this
	//currentState=MOVING_STATE;

    switch (currentState)
    {
/*
           case MOVING_STATE://DYING_STATE:
                glColor3f(1.0f, 1.0f, 1.0f); //white
                if (currentDeathFrame<5) {
                    switch(currentDeathFrame)
                    {
                      case 0:
                        drawMyPlane(myDeathAnimationImg1);
                        break;
                      case 1:
                        drawMyPlane(myDeathAnimationImg2);
                        break;
                      case 2:
                        drawMyPlane(myDeathAnimationImg3);
                        break;
                      case 3:
                        drawMyPlane(myDeathAnimationImg4);
                        break;
                      case 4:
                        drawMyPlane(myDeathAnimationImg5);
                        //changeState(MOVING_STATE);
                        break;
                    }
                }
                currentDeathFrame=(currentDeathFrame+1)%4;
                break;
*/
/* //removed by Mike, 20201014
           case INITIALIZING_STATE:
                if (invincibleCounter==10) {
                  changeState(MOVING_STATE);
                  setCollidable(true);
                }
                else invincibleCounter++;
*/
            case MOVING_STATE:
            	
                   //added by Mike, 20201001
                   drawModelRobotShip(); //TO-DO: -add: ModelPool.cpp
           	   	
				//removed by Mike, 20201001
/*           	                  	
               glColor3f(1.0f, 1.0f, 1.0f); //white
           	   glPushMatrix();	
                   if (rotationAngle>360)
                     rotationAngle-=360;
                   else if (rotationAngle<-360)
                     rotationAngle+=360;
                   //since the model ship faces the top, do this...
                   //glRotatef(-90, 1.0f, 0.0f, 0.0f);
                   //since the model ship is facing the opposite direction (in terms of Z)...
                   //glRotatef(180, 0.0f, 0.0f, 1.0f);
                   glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
                   //since the model ship is too big, do this...
                   glScalef(0.1f, 0.1f, 0.1f);

                   //removed by Mike, 20201001
                   if ((invincibleCounter%2)==0) //makes the ship blink when in INITIALIZING_STATE
                     drawModelValkyrie();

           	   	glPopMatrix();	// pop back to original coordinate system
*/                   
               break;
            case IN_TITLE_STATE:
               break;

    }    

	//removed by Mike, 20201001
//    glPopMatrix();	// pop back to original coordinate system
}

void RobotShip::update(float dt)
{
    switch (currentState)
    {
           case INITIALIZING_STATE:
           case MOVING_STATE:      
           		//added by Mike, 20201001
           		rotationAngle=0; //TO-DO: -update: this
           		
//                if (isMovingForward)
//                { 
  					//removed by Mike, 20201014
                    /* rotationAngle in degrees, convert to radians */
                    //im not yet sure why, but i have to deduct 90 to rotationAngle
//                    rotationAngleRad = (rotationAngle) * 3.141593f / 180.0f;

/*                  //removed by Mike, 20201001
                    yAccel = (cos(rotationAngleRad)*thrust);
                    xAccel = -(sin(rotationAngleRad)*thrust);
*/

/*
                   rotationAngle+=1;
                   char str[700];                                       
                   sprintf(str,"xAccel: %f",xAccel);
                   MessageBox(NULL, str, "Welcome!", MB_OK);
*/

/*
					//added by Mike, 20201001                   
					//TO-DO: -update: max acceleration
                    if (yAccel>0.01f) {
						thrust=0.01f;                    
					}
                    if (xAccel>0.01f) {
						thrust=0.01f;                    
					}
*/

/*					//removed by Mike, 20201001
                    xVel=xAccel;
                    yVel=yAccel;
*/                    
                    
/*					//removed by Mike, 20201014                    
                    if (xVel > maxXVel) xVel = maxXVel;
                    else if (xVel < -maxXVel) xVel = -maxXVel;
                    if (yVel > maxYVel) yVel = maxYVel;
                    else if (yVel < -maxYVel) yVel = -maxYVel;

                    myXPos+=xVel;
                    myYPos+=yVel;
                   
				    //note: deaccelerate 
                    if (thrust>0)
                      thrust-=0.02f; //0.01f
                    else thrust=0;
*/                                        

           		//wrap the world 
           		//edited by Mike, 20201001
/*           		
           		if (myXPos <= -25.0f) myXPos = 25.0f;
           		else if (myXPos > 25.0f) myXPos = -25.0f; 
           		if (myYPos <= -17.0f) myYPos = 19.0f;
           		else if (myYPos > 19.0f) myYPos = -17.0f;
*/
/*
           		if (myXPos <= -1.0f) myXPos = 1.0f;
           		else if (myXPos > 1.0f) myXPos = -1.0f; 
           		if (myYPos <= -1.0f) myYPos = 1.0f;
           		else if (myYPos > 1.0f) myYPos = -1.0f;
*/
				//note: add ship width and height
/*
           		if (myXPos+myWidth/2 <= -1.0f) myXPos = 1.0f-myWidth/2; //if left side
           		else if (myXPos+myWidth/2 >= 1.0f) myXPos = -1.0f+myWidth/2; //if right side
           		if (myYPos+myHeight/2 <= -1.0f) myYPos = 1.0f+myHeight/2; //if bottom side
           		else if (myYPos+myHeight/2 >= 1.0f) myYPos = -1.0f+myHeight/2; //if top side
*/
				//top-left anchor/origin/reference point
/*           	//TO-DO: -update: this	
				if (myXPos+myWidth/2 <= -1.0f) myXPos = 1.0f-myWidth/2; //if left side
           		else if (myXPos+myWidth/2 >= 1.0f) myXPos = -1.0f+myWidth/2; //if right side
*/           	

/*				//edited by Mike, 20201001	
           		if (myYPos+myHeight/2 >= 1.0f) myYPos = 0.0f+myHeight/2; //if bottom side
           		else if (myYPos+myHeight/2 <= 0.0f) myYPos = 1.0f-myHeight/2; //if top side
*/
/*
				//add velocity
           		if (myYPos+yVel >= 1.0f) myYPos = 0.0f+myHeight/3; //if bottom side
           		else if (myYPos+yVel <= 0.0f) myYPos = 1.0f-myHeight/3; //if top side
*/

				//edited by Mike, 20201015
/*
           		if (myXPos <= 0.0f) myXPos = 1.0f-myWidth/8; //if left side
           		else if (myXPos >= 1.0f) myXPos = 0.0f+myWidth/8; //if right side

           		if (myYPos >= 1.0f) myYPos = 0.0f+myHeight/8; //if bottom side
           		else if (myYPos <= 0.0f) myYPos = 1.0f-myHeight/8; //if top side
*/
/*				//removed by Mike, 20201023
				//TO-DO: -add: 0.1f*iColumnCountMax
           		if (myXPos <= 0.0f) myXPos = 0.1f*20-myWidth/8; //if left side
           		else if (myXPos >= 0.1f*20) myXPos = 0.0f+myWidth/8; //if right side

				//TO-DO: -add: 0.1f*iRowCountMax
           		if (myYPos >= 0.1f*20) myYPos = 0.0f+myHeight/8; //if bottom side
           		else if (myYPos <= 0.0f) myYPos = 0.1f*20-myHeight/8; //if top side
*/

/*
          char str[700];                                       
          sprintf(str,"myXPos: %f",myXPos);
          MessageBox(NULL, str, "Welcome!", MB_OK);
*/
//                   isMovingForward=0; 
//                }
                break;
            case IN_TITLE_STATE:                
                  rotationAngle+=5;//rotationStep;
                break;
            default: //STANDING STATE
              break;//do nothing    
    }
}

void RobotShip::changeState(int s)
{
  currentState=s;                  
}

void RobotShip::move(int key)
{
   switch (key)
   {
     case KEY_UP:
     case KEY_W:
          //isMovingForward=1;
          //myZPos-=1.0f;
/*          if (thrust<thrustMax)
            thrust+=0.1f;
*/      
          //added by Mike, 20201001            
	      myYPos+=-stepY;
          break;      
     case KEY_DOWN:
/*     	  //added by Mike, 20201001
          if (thrust<thrustMax)
            thrust+=-0.1f;
*/
          //added by Mike, 20201001            
	      myYPos+=stepY;
          break;      
     case KEY_LEFT:
     		//removed by Mike, 20201001
//          rotationAngle+=rotationStep;
/*		//removed by Mike, 20201014
     	  //added by Mike, 20201001
          if (thrust<thrustMax)
            thrust+=-0.1f;
*/
          //added by Mike, 20201001            
	      myXPos+=-stepX;

/*          
          char str[700];                                       
          sprintf(str,"rotationAngle: %f",rotationAngle);
          MessageBox(NULL, str, "Welcome!", MB_OK);
*/
          break;      
     case KEY_RIGHT:
     	//removed by Mike, 20201001
//          rotationAngle-=rotationStep;

/*		//removed by Mike, 20201014
     	  //added by Mike, 20201001
          if (thrust<thrustMax)
            thrust+=0.1f;
*/
          //added by Mike, 20201001            
	      myXPos+=stepX;
//          return;
		  break;
   }
}
void RobotShip::hitBy(MyDynamicObject* mdo)
{
     //changeState(DEATH_STATE);
     //setCollidable(false);
    myOpenGLCanvas->loseLife();
    
    //removed by Mike, 20201001
/*
	zing = sound->load_sound_clip(RESETSOUND);
	sound->play_sound_clip(zing);	
*/
    reset();    
}

void RobotShip::setOpenGLCanvas(OpenGLCanvas* c)
{
     myOpenGLCanvas = c;
}

void RobotShip::reset()
{
     changeState(INITIALIZING_STATE);
     myXPos=0;
     myYPos=0;
     rotationAngle=0.0f;
     thrust=0.0f;
     setCollidable(false);
     invincibleCounter=0;
}
int RobotShip::getState()
{
    return currentState;
}

//added by Mike, 20201016
void RobotShip::destroy()
{
/*	
	for(int i = 0; i < MAX_EXPLOSION_PARTICLES; ++i) {
	    delete [] explosionParticle[i];
	}
	delete [] explosionParticle;
*/
}
