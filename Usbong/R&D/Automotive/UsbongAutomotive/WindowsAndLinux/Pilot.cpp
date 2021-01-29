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
 * @date updated: 20210128
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

/*	//removed by Mike, 20201121
#include <gl/gl.h>
#include <gl/glu.h>
*/

//added by Mike, 20201121
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif

//edited by Mike, 20201207
#include "Pilot.h"

/* //TO-DO: -add: these
#include "PolygonUtils.h"
#include "ModelPool.h"
*/

#include <string.h>

//added by Mike, 20201207
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


//#include "ModelPool.h"

//edited by Mike, 20201014
//added by Mike, 20201001
enum Keys
{
/*	//edited by Mike, 20210128
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
*/
	//TO-DO: -verify: gamepad
/*	//edited by Mike, 20210129
	KEY_A = 0,
	KEY_D,
	KEY_W,
	KEY_S,
*/
	KEY_W = 0,
	KEY_S,
	KEY_D,
	KEY_A,

	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	KEY_ENTER,

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
GLboolean Pilot::test_pow2(GLushort i)
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
void Pilot::load_tga(char *filename)
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
void Pilot::setup()
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
void Pilot::drawModelPilot() {
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
	
	//added by Mike, 20201023; removed by Mike, 20201114
	//set square face with no color fill 
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	    glColor3f(1.0f, 0.0f, 0.0f); // Red
	
		//edited by Mike, 20201023
	//	drawCube();
		drawCube(myWidth); //myWidth = myHeight

	//added by Mike, 20201023; removed by Mike, 20201114
	//set square face with color fill 	
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

//edited by Mike, 20201001
//Pilot::Pilot(): MyDynamicObject(0,0,300)
//edited by Mike, 20201115
//Pilot::Pilot(): MyDynamicObject(0,0,0)
Pilot::Pilot(float xPos, float yPos, float zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,0.0f, windowWidth, windowHeight)
{ 
    //edited by Mike, 20201001
	//currentState=IN_TITLE_STATE;//MOVING_STATE;
	currentState=MOVING_STATE;
	//added by Mike, 20201201
	currentMovingState=IDLE_MOVING_STATE;

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
/*	//edited by Mike, 20201116
    stepX=0.1;
    stepY=0.1;
*/
    //edited by Mike, 20201025
    stepX=0.3;
    stepY=0.3;
    stepZ=0.3;

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

	//edited by Mike, 20201201    
	//TO-DO: -update: this
/*	myWidth=1.0f;
    myHeight=1.0f;
*/
	myWidth=1.4f;
    myHeight=1.4f;

    
/*
    myWidth=0.5f;
    myHeight=0.5f;
*/
	//added by Mike, 20201001; edited again by Mike, 20201001
	//note: initial position, top-left
/*    myXPos=0.0f;
    myYPos=0+myHeight;//0.1f;
*/
	//note: position: 3,3; width, height; count starts at 0
    myXPos=0.0f+myWidth*3;
    //edited by Mike, 2020116
//    myYPos=0.0f+myHeight*3;
    myZPos=0.0f+myHeight*3;

	//added by Mike, 20201115
	myWindowWidth=windowWidth;
	myWindowHeight=windowHeight;
	

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

    //edited by Mike, 20201201	
	currentFacingState=FACING_UP;

	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;


	loadTexture(myBodyTexture, "bodyTexture.tga", &myBodyTextureObject);
	loadTexture(myHeadTexture, "headTexture.tga", &myHeadTextureObject);	

	//removed by Mike, 20201001
//	setup();
	
    setCollidable(true);
    
    
    
    
}

Pilot::~Pilot()
{
}

float* Pilot::getXYZPos()
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
void Pilot::drawPilot()
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

	//edited by Mike, 20201116
    glTranslatef(myXPos, myYPos, myZPos);
//    glTranslatef(myXPos, myZPos, myYPos);    

	//added by Mike, 20201201
    if (currentFacingState==FACING_LEFT) 
    {  
        glRotatef(90, 0.0f, 1.0f, 0.0f);
    } 
    else if (currentFacingState==FACING_RIGHT) 
    {
        glTranslatef(0.0f, 0.0f, -myWidth/3); 
        glRotatef(-90, 0.0f, 1.0f, 0.0f);
    }
    else if (currentFacingState==FACING_UP)
    {
        //glTranslatef(-myWidthX/3, 0.0f, 0.0f); 
    }
    else if (currentFacingState==FACING_DOWN)
    {
        glTranslatef(myWidth/3, 0.0f, 0.0f); 
        glRotatef(180, 0.0f, 1.0f, 0.0f);
    }

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
			//TO-DO: -add: STANDING_STATE
/*  //removed by Mike, 20201130
                   //added by Mike, 20201001
                   drawModelPilot(); //TO-DO: -add: ModelPool.cpp
*/
				//added by Mike, 20201201; edited by Mike, 20201207
				//human pilot at smaller scale than Robotship Mecha
//		                glScalef(1.0f, 1.0f, 1.0f);			
		                glScalef(1.5f, 1.5f, 1.5f);
//		                glScalef(4.0f, 4.0f, 4.0f);		

				switch(currentMovingState) {
		            case IDLE_MOVING_STATE:		
						//edited by Mike, 20201204
/*
							glPushMatrix();	
							   drawUpperArm(-0.1f, 0.0f, 0.0f); //left
							   drawUpperArm(0.3f, 0.0f, 0.0f); //right        
							   drawLowerArm(-0.1f, -0.2f, 0.0f); //left
							   drawLowerArm(0.3f, -0.2f, 0.0f); //right

							   drawUpperLeg(0.0f, -0.5f, 0.0f); //left
							   drawUpperLeg(0.2f, -0.5f, 0.0f); //right        

							   drawLowerLeg(0.0f, -0.7f, 0.0f); //left
							   drawLowerLeg(0.2f, -0.7f, 0.0f); //right

							   //added by Mike, 20201201
							   drawHead(0.1f, 0.2f, 0.0f);		  
							   drawBody(0.1f, -0.15f, 0.0f);
							 glPopMatrix();	// pop back to original coordinate system
*/	

						if ((currentFacingState==FACING_UP)
					    	|| (currentFacingState==FACING_LEFT))
					    {
							glPushMatrix();	
//							   drawUpperArm(-0.1f, 0.0f, 0.0f); //left
							   drawUpperArm(0.3f, 0.0f, 0.0f); //right        
//							   drawLowerArm(-0.1f, -0.2f, 0.0f); //left
							   drawLowerArm(0.3f, -0.2f, 0.0f); //right

							   drawUpperLeg(0.0f, -0.5f, 0.0f); //left
							   drawUpperLeg(0.2f, -0.5f, 0.0f); //right        

							   drawLowerLeg(0.0f, -0.7f, 0.0f); //left
							   drawLowerLeg(0.2f, -0.7f, 0.0f); //right

							   //added by Mike, 20201201; edited by Mike, 20201204
							   drawBody(0.1f, -0.15f, 0.0f);
							   drawHead(0.1f, 0.2f, 0.0f);		  

							   drawUpperArm(-0.1f, 0.0f, 0.0f); //left
							   drawLowerArm(-0.1f, -0.2f, 0.0f); //left
							glPopMatrix();	// pop back to original coordinate system	
						}
					    else if ((currentFacingState==FACING_DOWN)
					    		|| (currentFacingState==FACING_RIGHT))
					    {
							glPushMatrix();	
							   drawUpperArm(-0.1f, 0.0f, 0.0f); //left
//							   drawUpperArm(0.3f, 0.0f, 0.0f); //right        
							   drawLowerArm(-0.1f, -0.2f, 0.0f); //left
//							   drawLowerArm(0.3f, -0.2f, 0.0f); //right

							   drawUpperLeg(0.0f, -0.5f, 0.0f); //left
							   drawUpperLeg(0.2f, -0.5f, 0.0f); //right        

							   drawLowerLeg(0.0f, -0.7f, 0.0f); //left
							   drawLowerLeg(0.2f, -0.7f, 0.0f); //right

							   //added by Mike, 20201201; edited by Mike, 20201204
							   drawBody(0.1f, -0.15f, 0.0f);
							   drawHead(0.1f, 0.2f, 0.0f);		  

							   drawUpperArm(0.3f, 0.0f, 0.0f); //right        
							   drawLowerArm(0.3f, -0.2f, 0.0f); //right
							glPopMatrix();	// pop back to original coordinate system	
						}						
						break;
					case WALKING_MOVING_STATE:
						//added by Mike, 20201202
						if ((currentFacingState==FACING_UP)
					    	|| (currentFacingState==FACING_LEFT))
					    {
			            	glPushMatrix();			            
			                    //ARMS
/*								/removed by Mike, 20201202 due to draw sequence is important
			                    //UPPER
			            		glPushMatrix();
			            			glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
			            			drawUpperArm(-0.1f, 0.0f, 0.0f); //left
			                		glPushMatrix();
			                            glTranslatef(0.0f, 0.0f, 0.1f);
			                			glRotatef(45, 1.0f, 0.0f, 0.0f);
			                		    drawLowerArm(-0.1f, -0.3f, 0.0f); //left
			                		glPopMatrix();
			            		glPopMatrix();
*/
			            		glPushMatrix();
			            			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			                        drawUpperArm(0.3f, 0.0f, 0.0f); //right        
			                		glPushMatrix();
			                            glTranslatef(0.0f, 0.0f, 0.1f);
			                			glRotatef(45, 1.0f, 0.0f, 0.0f);
			                            drawLowerArm(0.3f, -0.3f, 0.0f); //right
			                		glPopMatrix();
			            		glPopMatrix();
			                    //LEGS
			            		glPushMatrix();					
			            			glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
			            		    drawUpperLeg(0.0f, -0.5f, 0.0f); //left
			               		    glPushMatrix();
			                            //glTranslatef(0.0f, 0.0f, 0.1f);
			                			//glRotatef(5, 1.0f, 0.0f, 0.0f);
			            		        drawLowerLeg(0.0f, -0.7f, 0.0f); //left
			                		glPopMatrix();
			            		glPopMatrix();
			            		glPushMatrix();					
			            			glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			                        drawUpperLeg(0.2f, -0.5f, 0.0f); //right        
			               		    glPushMatrix();
			                            //glTranslatef(0.0f, 0.0f, 0.1f);
			                			//glRotatef(5, 1.0f, 0.0f, 0.0f);
			                            drawLowerLeg(0.2f, -0.7f, 0.0f); //right
			                		glPopMatrix();
			            		glPopMatrix();
	
							    //added by Mike, 20201202; edited by Mike, 20201204
			            		drawBody(0.1f, -0.15f, 0.0f);	
			            		drawHead(0.1f, 0.2f, 0.0f);		

			                    //UPPER
			            		glPushMatrix();
			            			glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
			            			drawUpperArm(-0.1f, 0.0f, 0.0f); //left
			                		glPushMatrix();
			                            glTranslatef(0.0f, 0.0f, 0.1f);
			                			glRotatef(45, 1.0f, 0.0f, 0.0f);
			                		    drawLowerArm(-0.1f, -0.3f, 0.0f); //left
			                		glPopMatrix();
			            		glPopMatrix();
	
			            	glPopMatrix();	// pop back to original coordinate system						
					    }
					    else if ((currentFacingState==FACING_DOWN)
					    		|| (currentFacingState==FACING_RIGHT))
					    {
			            	glPushMatrix();			            
			                    //ARMS
			                    //UPPER
			            		glPushMatrix();
			            			glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
			            			drawUpperArm(-0.1f, 0.0f, 0.0f); //left
			                		glPushMatrix();
			                            glTranslatef(0.0f, 0.0f, 0.1f);
			                			glRotatef(45, 1.0f, 0.0f, 0.0f);
			                		    drawLowerArm(-0.1f, -0.3f, 0.0f); //left
			                		glPopMatrix();
			            		glPopMatrix();
/*								/removed by Mike, 20201202 due to draw sequence is important
			            		glPushMatrix();
			            			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			                        drawUpperArm(0.3f, 0.0f, 0.0f); //right        
			                		glPushMatrix();
			                            glTranslatef(0.0f, 0.0f, 0.1f);
			                			glRotatef(45, 1.0f, 0.0f, 0.0f);
			                            drawLowerArm(0.3f, -0.3f, 0.0f); //right
			                		glPopMatrix();
			            		glPopMatrix();
*/	
			                    //LEGS
			            		glPushMatrix();					
			            			glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
			            		    drawUpperLeg(0.0f, -0.5f, 0.0f); //left
			               		    glPushMatrix();
			                            //glTranslatef(0.0f, 0.0f, 0.1f);
			                			//glRotatef(5, 1.0f, 0.0f, 0.0f);
			            		        drawLowerLeg(0.0f, -0.7f, 0.0f); //left
			                		glPopMatrix();
			            		glPopMatrix();
			            		glPushMatrix();					
			            			glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			                        drawUpperLeg(0.2f, -0.5f, 0.0f); //right        
			               		    glPushMatrix();
			                            //glTranslatef(0.0f, 0.0f, 0.1f);
			                			//glRotatef(5, 1.0f, 0.0f, 0.0f);
			                            drawLowerLeg(0.2f, -0.7f, 0.0f); //right
			                		glPopMatrix();
			            		glPopMatrix();
	
							    //added by Mike, 20201202; edited by Mike, 20201204
			            		drawBody(0.1f, -0.15f, 0.0f);
			            		drawHead(0.1f, 0.2f, 0.0f);		

			            		glPushMatrix();
			            			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
			                        drawUpperArm(0.3f, 0.0f, 0.0f); //right        
			                		glPushMatrix();
			                            glTranslatef(0.0f, 0.0f, 0.1f);
			                			glRotatef(45, 1.0f, 0.0f, 0.0f);
			                            drawLowerArm(0.3f, -0.3f, 0.0f); //right
			                		glPopMatrix();
			            		glPopMatrix();
	
	
			            	glPopMatrix();	// pop back to original coordinate system						
					    }

/*
		            	glPushMatrix();			            
		                    //ARMS
		                    //UPPER
		            		glPushMatrix();
		            			glRotatef(armAngles[LEFT], 1.0f, 0.0f, 0.0f);
		            			drawUpperArm(-0.1f, 0.0f, 0.0f); //left
		                		glPushMatrix();
		                            glTranslatef(0.0f, 0.0f, 0.1f);
		                			glRotatef(45, 1.0f, 0.0f, 0.0f);
		                		    drawLowerArm(-0.1f, -0.3f, 0.0f); //left
		                		glPopMatrix();
		            		glPopMatrix();

							//added by Mike, 20201202
//		            		drawBody(0.1f, -0.15f, 0.0f);

		            		glPushMatrix();
		            			glRotatef(armAngles[RIGHT], 1.0f, 0.0f, 0.0f);
		                        drawUpperArm(0.3f, 0.0f, 0.0f); //right        
		                		glPushMatrix();
		                            glTranslatef(0.0f, 0.0f, 0.1f);
		                			glRotatef(45, 1.0f, 0.0f, 0.0f);
		                            drawLowerArm(0.3f, -0.3f, 0.0f); //right
		                		glPopMatrix();
		            		glPopMatrix();

		                    //LEGS
		            		glPushMatrix();					
		            			glRotatef(legAngles[LEFT], 1.0f, 0.0f, 0.0f);
		            		    drawUpperLeg(0.0f, -0.5f, 0.0f); //left
		               		    glPushMatrix();
		                            //glTranslatef(0.0f, 0.0f, 0.1f);
		                			//glRotatef(5, 1.0f, 0.0f, 0.0f);
		            		        drawLowerLeg(0.0f, -0.7f, 0.0f); //left
		                		glPopMatrix();
		            		glPopMatrix();
		            		glPushMatrix();					
		            			glRotatef(legAngles[RIGHT], 1.0f, 0.0f, 0.0f);
		                        drawUpperLeg(0.2f, -0.5f, 0.0f); //right        
		               		    glPushMatrix();
		                            //glTranslatef(0.0f, 0.0f, 0.1f);
		                			//glRotatef(5, 1.0f, 0.0f, 0.0f);
		                            drawLowerLeg(0.2f, -0.7f, 0.0f); //right
		                		glPopMatrix();
		            		glPopMatrix();

							//added by Mike, 20201202
		            		drawHead(0.1f, 0.2f, 0.0f);		
		            		drawBody(0.1f, -0.15f, 0.0f);

		            	glPopMatrix();	// pop back to original coordinate system						
*/
						break;
				}

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

void Pilot::update(float dt)
{
    switch (currentState)
    {
           case INITIALIZING_STATE:
           case MOVING_STATE:      
				switch(currentMovingState) {
		           case WALKING_MOVING_STATE:
		                //note: Code structure taken from Dave Astle and Kevin Hawkins's code 
		                //("Beginning OpenGL Game Programming", Chapter 4)
		                //-Mike, Dec. 21, 2006
		            	// if leg is moving forward, increase angle, else decrease angle
		            	for (char side = 0; side < 2; side++)
		            	{
		            		// arms
/* 	//edited by Mike, 20201204							
		            		if (armStates[side] == FORWARD_STATE)
		            			armAngles[side] += 25.0f * dt;//20.0f * dt;
		            		else
		            			armAngles[side] -= 30.0f * dt;//20.0f * dt;
*/
		            		if (armStates[side] == FORWARD_STATE)
		            			armAngles[side] += 8.3f * dt;//20.0f * dt;
		            		else
		            			armAngles[side] -= 10.0f * dt;//20.0f * dt;
							
		            		// change state if exceeding angles
		            		if (armAngles[side] >= 25.0f) //15.0f
		            			armStates[side] = BACKWARD_STATE;
		            		else if (armAngles[side] <= -45.0f) //15.0f
		            			armStates[side] = FORWARD_STATE;
		            
		            		// legs
/*							//edited by Mike, 20201204
							if (legStates[side] == FORWARD_STATE)
		            			legAngles[side] += 15.0f * dt;
		            		else
		            			legAngles[side] -= 15.0f * dt;
*/
							if (legStates[side] == FORWARD_STATE)
		            			legAngles[side] += 5.0f * dt;
		            		else
		            			legAngles[side] -= 5.0f * dt;
							
		            		// change state if exceeding angles
		            		if (legAngles[side] >= 15.0f) //15.0f
		            			legStates[side] = BACKWARD_STATE;
		            		else if (legAngles[side] <= -15.0f)
		            			legStates[side] = FORWARD_STATE;		
		            	}                
		                break;
		            default: //STANDING STATE
		              break;//do nothing    
				}
				
				
				//TO-DO: -add: these
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

				//Note: Use these with update to OpenGLCanvas
           		//wrap the world 
           		//edited by Mike, 20201116
//           		if (myXPos <= 0.0f) myXPos = 20-myWidth/8; //if left side
           		if (myXPos <= 0.0f) myXPos = myWindowWidth/100-myWidth/8; //if left side
           		else if (myXPos >= myWindowWidth/100) myXPos = 0.0f+myWidth/8; //if right side

           		if (myZPos >= myWindowHeight/100) myZPos = 0.0f+myHeight/8; //if bottom side
           		//edited by Mike, 20201116
//           		else if (myZPos <= 0.0f) myZPos = 20-myHeight/8; //if top side
           		else if (myZPos <= 0.0f) myZPos = myWindowHeight/100-myHeight/8; //if top side
           		           		


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

void Pilot::changeState(int s)
{
  currentState=s;                  
}

void Pilot::move(int key)
{
   //added by Mike, 20201201
   currentMovingState=WALKING_MOVING_STATE;

   switch (key)
   {
     case KEY_UP:
     case KEY_W:
          //isMovingForward=1;
          //myZPos-=1.0f;
/*          if (thrust<thrustMax)
            thrust+=0.1f;
*/      
          //added by Mike, 20201001; edited by Mike, 20201116
//	      myYPos+=-stepY;
	      myZPos+=-stepZ;
	      
	      //added by Mike, 20201201
          currentFacingState=FACING_UP;
          break;      
     case KEY_DOWN:
/*     	  //added by Mike, 20201001
          if (thrust<thrustMax)
            thrust+=-0.1f;
*/
          //added by Mike, 20201001; edited by Mike, 20201116
//	      myYPos+=stepY;
	      myZPos+=stepZ;

	      //added by Mike, 20201201
          currentFacingState=FACING_DOWN;
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
	      //added by Mike, 20201201
          currentFacingState=FACING_LEFT;
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

	      //added by Mike, 20201201
          currentFacingState=FACING_RIGHT;
		  break;
		//added by Mike, 20201201
		default:
		  currentMovingState=IDLE_MOVING_STATE;
		  break;
   }
}
void Pilot::hitBy(MyDynamicObject* mdo)
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

void Pilot::setOpenGLCanvas(OpenGLCanvas* c)
{
     myOpenGLCanvas = c;
}

void Pilot::reset()
{
     changeState(INITIALIZING_STATE);
     myXPos=0;
     myYPos=0;
     rotationAngle=0.0f;
     thrust=0.0f;
     setCollidable(false);
     invincibleCounter=0;
}
int Pilot::getState()
{
    return currentState;
}

//added by Mike, 20201016
void Pilot::destroy()
{
/*	
	for(int i = 0; i < MAX_EXPLOSION_PARTICLES; ++i) {
	    delete [] explosionParticle[i];
	}
	delete [] explosionParticle;
*/
}

//added by Mike, 20201130
//TO-DO: -add: in PolygonUtils
//--------------------------------------------
bool Pilot::loadTexture(CTargaImage *myTexture, const char *filename, unsigned int *myTextureObject)
{
    //note: Code taken from Dave Astle and Kevin Hawkins's code 
    //("Beginning OpenGL Game Programming", Chapter 7)
    //with slight modifications from Mike
    //-Mike, Dec. 21, 2006
	// enable 2D texturing
	glEnable(GL_TEXTURE_2D);

    myTexture = new CTargaImage;
   	if (!myTexture->Load(filename))//opengl_logo.tga //background.tga //rock.tga
		return false;

    // retrieve "unused" texture object
	//glGenTextures(1, &myTextureObject);
	glGenTextures(1, myTextureObject);

	// bind the texture object
	//glBindTexture(GL_TEXTURE_2D, myTextureObject);
	glBindTexture(GL_TEXTURE_2D, *myTextureObject);

	// minimum required to set the min and mag texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// now that the texture object is bound, specify a texture for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myTexture->GetWidth(), myTexture->GetHeight(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, myTexture->GetImage());

	//added by Mike, 20201207
	return true;
}

void Pilot::drawTriangledCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_TRIANGLES);
		//note: must be in correct order, counter-clockwise
            //glColor3f(1.0f, 0.0f, 0.0f);	// red
            //note: this must be clock-wise so that it will face backwards
		    //front face		    
            //part 1  
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);          

            //part 2
            glVertex3f(-0.5f, 0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);

            //glColor3f(0.5f, 0.0f, 0.0f);	// dark red
            //back face 
            //part 1
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, 0.5f);
            //part 2
            glVertex3f(-0.5f, 0.5f, 0.5f);          
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            
    		//glColor3f(0.0f, 1.0f, 0.0f);	// green
            //right face
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, 0.5f);
            //part 2
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, 0.5f);          

    		//glColor3f(0.0f, 0.5f, 0.0f);	// dark green
            //left face
            //part 1
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, 0.5f);          

            //part 2
            glVertex3f(-0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);

    		//glColor3f(0.0f, 0.0f, 1.0f);	// blue
            //top face
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);
            //part 2
            glVertex3f(-0.5f, 0.5f, 0.5f);
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);          

    		//glColor3f(0.0f, 0.0f, 0.5f);	// dark blue
            //bottom face
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);          

            //part 2
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
	glPopMatrix();     
}

void Pilot::drawUpperArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		//glColor3f(1.0f, 0.0f, 0.0f);	// red
		glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(xPos, yPos, zPos);
		glScalef(0.1f, 0.2f, 0.1f);		
        drawTriangledCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Pilot::drawLowerArm(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		//glColor3f(0.5f, 0.0f, 0.0f);	// dark red
		glColor3f(0.8f, 0.8f, 0.8f);
		glTranslatef(xPos, yPos, zPos);
		glScalef(0.1f, 0.3f, 0.1f);		// arm is a 1x4x1 cube
        drawTriangledCube(0.0f, 0.0f, 0.0f);
		//drawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

/*	//removed by Mike, 20201130
void Pilot::drawAntenna(float xPos, float yPos, float zPos)
{
		glColor3f(0.2f, 0.2f, 0.2f);	// dark gray
        //left side
        glPushMatrix();        
    		glTranslatef(-0.12f, 0.0f, 0.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    		glScalef(0.1f, 0.6f, 0.1f);
            drawTriangle(0.0f, 0.0f, 0.0f);
        glPopMatrix();
        //right side
        glPushMatrix();        
    		glTranslatef(0.12f, 0.0f, 0.0f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    		glScalef(0.1f, 0.6f, 0.1f);
            drawTriangle(0.0f, 0.0f, 0.0f);
        glPopMatrix();
}
*/

void Pilot::drawHead(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		//removed by Mike, 20201130
//        drawAntenna(0.0f, 0.0f, 0.0f);		
		glColor3f(1.0f, 1.0f, 1.0f);	// white		
		//glScalef(2.0f, 2.0f, 2.0f);		// head is a 2x2x2 cube
		glScalef(0.2f, 0.2f, 0.2f);

		glBindTexture(GL_TEXTURE_2D, myHeadTextureObject);
        glEnable(GL_TEXTURE_2D); //added by Mike, Dec.21,2006

		//edited by Mike, 20201204
		//glColor3f(1.0f, 1.0f, 1.0f);//default: white
		glColor3f(0.97f, 0.09f, 0.0f);//red

    	glBegin(GL_TRIANGLE_STRIP);
    	    //note: In "glTexCoord2f(1.0, 0.0);", if 1.0 is changed to 2.0, the plane is made up of 4 images instead of just 1 whole image 
    		glTexCoord2f(1.0, 0.0); 
            glVertex3f(0.5f, -0.5f, -0.5f);
    		glTexCoord2f(0.0, 0.0); 
            glVertex3f(-0.5f, -0.5f, -0.5f);
    		//note: i don't know why, but i have to create a triangle first, 
            //then connect the last point of the square next, -Mike, Dec. 22, 2006
            //a
            glTexCoord2f(1.0, 1.0);	
            glVertex3f(0.5f, 0.5f, -0.5f);
    		//b
            glTexCoord2f(0.0, 1.0);	
            glVertex3f(-0.5f, 0.5f, -0.5f);
    	glEnd();    	
        drawTriangledCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Pilot::drawBody(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		//glColor3f(0.0f, 0.0f, 1.0f);	// blue
		//glColor3f(0.0f, 0.0f, 0.0f);	// black
        glTranslatef(xPos, yPos, zPos);
//		glScalef( 0.2f, 0.2f, 0.1f);
//		drawSphere();
		glScalef(0.3f, 0.5f, 0.2f);
		glBindTexture(GL_TEXTURE_2D, myBodyTextureObject);
        glEnable(GL_TEXTURE_2D); //added by Mike, Dec.21,2006

		//edited by Mike, 20201204
	    //glColor3f(1.0f, 1.0f, 1.0f);//default: white
	    glColor3f(0.06f, 0.54f, 0.0f);	//green

    	glBegin(GL_TRIANGLE_STRIP);
    	    //note: In "glTexCoord2f(1.0, 0.0);", if 1.0 is changed to 2.0, the plane is made up of 4 images instead of just 1 whole image 
    		glTexCoord2f(1.0, 0.0); 
            glVertex3f(0.5f, -0.5f, -0.5f);
    		glTexCoord2f(0.0, 0.0); 
            glVertex3f(-0.5f, -0.5f, -0.5f);
    		//note: i don't know why, but i have to create a triangle first, 
            //then connect the last point of the square next, -Mike, Dec. 22, 2006
            //a
            glTexCoord2f(1.0, 1.0);	
            glVertex3f(0.5f, 0.5f, -0.5f);
    		//b
            glTexCoord2f(0.0, 1.0);	
            glVertex3f(-0.5f, 0.5f, -0.5f);
    	glEnd();    	
        drawTriangledCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Pilot::drawUpperLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		
		glScalef(0.1f, 0.25f, 0.1f);	
		//glColor3f(1.0f, 1.0f, 0.0f);	// yellow
		glColor3f(0.8f, 0.8f, 0.8f); //gray
        //drawCube(0.0f, 0.0f, 0.0f);
        drawTriangledCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Pilot::drawLowerLeg(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		
		// draw the foot
		glPushMatrix();
			glTranslatef(0.0f, 0.25f, -0.1f);
			//drawFoot(0.0f, -5.0f, 0.0f);
			//removed by Mike, 20201201
//			drawFoot(0.0f, -0.4f, 0.0f);
		glPopMatrix();		
		
		glScalef(0.1f, 0.25f, 0.1f);		// leg is a 1x5x1 cube
		//glColor3f(0.8f, 0.8f, 0.0f);	// yellow
        glColor3f(1.0f, 1.0f, 1.0f); //white
        drawTriangledCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}

void Pilot::drawFoot(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		//glColor3f(1.0f, 1.0f, 1.0f);
		glColor3f(0.2f, 0.2f, 0.2f);	// dark gray
		glTranslatef(xPos, yPos, zPos);
		//glScalef(1.0f, 0.5f, 3.0f);
		glScalef(0.1f, 0.05f, 0.3f);
        drawTriangledCube(0.0f, 0.0f, 0.0f);
		//drawCube(0.0f, 0.0f, 0.0f);
	glPopMatrix();
}
//--------------------------------------------


