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
 * @date created: 20201118
 * @date updated: 20210310
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//#include <SDL.h>

//added by Mike, 20201010
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif


#include <stdio.h>
#include <stdlib.h>

//edited by Mike, 20201011
#include <string.h>
//#include <string> //edited by mike, 20210209


//added by Mike, 20201011
#include <iostream>

//added by Mike, 20201118
#include "Level.h"

//added by Mike, 20210208
#include "UsbongUtils.h"

/*****************************************************************************/

/* texture loading */

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

GLboolean Level::test_pow2(GLushort i)
{
    while (i % 2 == 0)
        i /= 2;
    if (i == 1)
        return GL_TRUE;
    else
        return GL_FALSE;
}

//edited by Mike, 20201010
void Level::load_tga(char *filename)
//void load_tga(std::string filename)
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
        return;
    }

    /* read targa file into memory */
    data = (GLubyte *) malloc(targa.width * targa.height * 4);
    if (fread(data, targa.width * targa.height * 4, 1, file) != 1)
    {
        fclose(file);
        free(data);
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

/*	//edited by Mike, 20201123
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, targa.width, targa.height,
                      GL_RGB, GL_UNSIGNED_BYTE, data);
*/

    free(data);
    
/*   char str[700];                                       
   sprintf(str,"dito: %f",0.0f);
*/
//   std::cout << "keydown " << "\n";
	//printf("dito");
}

/*****************************************************************************/

/* text drawing */

//TO-DO: -update: this
//note: 10x16 each font character/level texture
//edited by Mike, 20201117
//void draw_char(GLfloat x, GLfloat y, char c)
void Level::draw_char(GLfloat x, GLfloat y, GLfloat z, char c)
{
	//edited by Mike, 20201117
//    GLfloat tx, ty;
    GLfloat tx, ty, tz;

    // check if the character is valid
    if (c < ' ' || c > '~')
        return;

    // subtract 32, since the first character in the font texture
    // is the space (ascii value 32)
    c = c - 32;

    // determine texture coordinates; this assumes that each character
    // in the font texture has a width-height ratio of 10:16 (see the
    // font.tga file to understand what I mean)
    tx = c % 12 * 0.078125f;
    ty = 0.875f - (c / 12 * 0.125f);
    //added by Mike, 20201117
//    tz = 0.875f - (c / 12 * 0.125f);

	//edited by Mike, 20201012
	//to make anchor/origin/reference point start at top-left
   //edited by Mike, 20201118
//    glTranslatef(0.0f, 0.1f, 0.0f);
	//note: use scale command if necessary
	//removed by Mike, 20201119
//    glTranslatef(0.0f, 0.0f, 1.0f); //add this due to set location of quad vertices
//    glTranslatef(0.0f, 0.0f, 0.3f); //add this due to size of square in grid 
	
	//removed by Mike, 20201119
//	glColor3f(1.0f, 1.0f, 1.0f); //set to default, i.e. white
    //glColor3f(0.0f, 0.0f, 0.0f); //set to default, i.e. black

/*	//edited by Mike, 20201118
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glTexCoord2f(tx, ty);
        glVertex3f(x, y, 0.0f);
        glTexCoord2f(tx + 0.078125f, ty);
      	glVertex3f(x+0.1f, y, 0.0f);      
        glTexCoord2f(tx + 0.078125f, ty + 0.125f);
      	glVertex3f(x+0.1f, y-0.16f, 0.0f);              
		glTexCoord2f(tx, ty + 0.125f);
      	glVertex3f(x, y-0.16f, 0.0f);      
   glEnd();        
*/

	//edited by Mike, 20201120
/*
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
        glTexCoord2f(tx, ty);
        //edited by Mike, 20201118
//        glVertex3f(x, y, 0.0f);
        glVertex3f(x, 0.0f, y);
 
        glTexCoord2f(tx + 0.078125f, ty);
        //edited by Mike, 20201118
//      	glVertex3f(x+0.1f, y, 0.0f);      
//      	glVertex3f(x+0.1f, 0.0f, y);      
		//edited by Mike, 20201119
//      	glVertex3f(x+1.0f, 0.0f, y);      
      	glVertex3f(x+1.2f, 0.0f, y);      
        glTexCoord2f(tx + 0.078125f, ty + 0.125f);
        //edited by Mike, 20201118
//      	glVertex3f(x+0.1f, y-0.16f, 0.0f);              
//      	glVertex3f(x+0.1f, 0.0f, y-0.16f);              
		//edited by Mike, 20201119
//      	glVertex3f(x+1.0f, 0.0f, y-1.6f);  
		//edited by Mike, 20201120            
//      	glVertex3f(x+1.2f, 0.0f, y-1.6f);              
      	glVertex3f(x+1.2f, 0.0f, y-1.2f);              
		glTexCoord2f(tx, ty + 0.125f);
        //edited by Mike, 20201118
//      	glVertex3f(x, y-0.16f, 0.0f);      
//      	glVertex3f(x, 0.0f, y-0.16f);      
		//edited by Mike, 20201120            
//      	glVertex3f(x, 0.0f, y-1.6f);      
      	glVertex3f(x, 0.0f, y-1.2f);      
   glEnd();        
*/

	//TO-DO: -update: this
	//TO-DO: -remove: auto-drawing of not seen from camera
	//drawCubeWithBlockTexture(fSideLength, tx, ty, tz);
	drawCubeWithBlockTexture(1.0f, tx, ty, tz, x,y,z);
//	drawCubeWithBlockTexture(2.0f, tx, ty, tz);
}

//edited by Mike, 20201118
//void draw_string(GLfloat x, GLfloat y, char *string)
//void draw_string(GLfloat x, GLfloat y, GLfloat z, char *string)
void Level::draw_level(GLfloat x, GLfloat y, GLfloat z, char *string)
{

    GLfloat origX=x;
    while (string[0] != 0)
    {

/*		//removed by Mike, 20201119
		//TO-DO: -update: this
        //added by Mike, Feb14,2007
		if (string[0]=='\n') {
			y -= 0.1f;//15.0f;
			x=origX-0.1f;//-10.0f;			
    	}
*/        

        glPushMatrix();
        	//removed by Mike, 20201010
            //make font larger, added by Mike, Feb28,2007
//            glScalef(2.0f, 2.0f, 2.0f);//1.5f, 1.5f, 1.5f);

//            glScalef(0.5f, 0.5f, 0.5f);
				//edited by Mike, 2020117
//            draw_char(x, y, string[0]);
				//edited by Mike, 20201120
//            draw_char(x, z, y, string[0]);
            draw_char(x, y, z, string[0]);

    	glPopMatrix();

        
        // advance 10 pixels after each character
//TO-DO: -update: this
//        x += 10.0f;

		//removed by Mike, 20201119
//        x += 0.1f;

        // go to the next character in the string
        string++;
    }    
}

//added by Mike, 20210208
//TO-DO: -add: read input .txt file
//TO-DO: -add: water tiles; pilot in water, no firing; RobotShip in water, firing OK; 
//note: palaka
void Level::drawLevelMapInViewPort(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fXSize, GLfloat fYSize, GLfloat fZSize) {
	int myWindowWidth=6144;
    int myWindowHeight=6144;

	int iRowCountMax=30;
 	int iColumnCountMax=30;
 	int iHeightCountMax=30; //added by Mike, 20210208

/*
	int iRowCountMax=MAX_Z_AXIS_VIEWPORT;
 	int iColumnCountMax=MAX_Z_AXIS_VIEWPORT;
 	int iHeightCountMax=MAX_Z_AXIS_VIEWPORT;
*/

	float fGridSquareWidth = myWindowWidth/iColumnCountMax/100.0;
	float fGridSquareHeight = myWindowHeight/iRowCountMax/100.0;
	
	char tempText[50];
	
	//TO-DO: -reverify: viewPort scrolling movement
/*
	fZ=fZ-1;
	fX=fX-1;
	fY=fY-1;
*/	
	//added by Mike, 20210305; added again by Mike, 20210308
	int iX=fX;
	int iY=fY;
	int iZ=fZ;
	
/*	
	int iX=fX/2;
	int iY=fY/2;
	int iZ=fZ/2;
*/	

/*	//removed by Mike, 20210308
	int iX=fX/(iColumnCountMax*fGridSquareWidth) - iColumnCountMax*fGridSquareWidth;
	int iY=fY/(iColumnCountMax*fGridSquareWidth);
	int iZ=fZ/(iRowCountMax*fGridSquareHeight) - iRowCountMax*fGridSquareHeight;
	
	if (iZ<0) {
		iZ=0;
	}
	else if (iZ>(iRowCountMax*fGridSquareHeight)) {
		iZ=iRowCountMax*fGridSquareHeight;
	}
	
	
	if (iX<0) {
		iX=0;
	}
	else if (iX>(iColumnCountMax*fGridSquareWidth)) {
		iX=iColumnCountMax*fGridSquareWidth;
	}
*/

	
/*
	for (int iRowCount=0; iRowCount<10; iRowCount++) {	
	 	for (int iColumnCount=0; iColumnCount<10; iColumnCount++) {		
//	 		printf("%s",sCurrentLevelMapContainer[iRowCount][iColumnCount]);
			std::cout << sCurrentLevelMapContainer[iRowCount][iColumnCount];
		}
			printf("\n");			
	}	
*/	
/*
	//added by Mike, 20201122
    //Grass
	sprintf(tempText,"G");
	//added by Mike, 20201124
    glColor3f(0.14f, 0.68f, 0.06f); // Green
 	for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {	
	 	for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {		
			//added by Mike, 20201124
			//execute this when using solid colors
			//for computer to not draw borders
			glBindTexture( GL_TEXTURE_2D, 0 );
			draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
		}
	}
*/	


//	printf("draw!");
//   std::cout << "iZ: " << iZ << "\n";
	
/*	
   std::cout << "MAX_Z_AXIS_VIEWPORT: " << MAX_Z_AXIS_VIEWPORT << "\n";
*/	
	
	
//   std::cout << "sCurrentLevelMapContainer: " << sCurrentLevelMapContainer[96][10] << "\n";
	
   //RobotShip Step: 0.3f
/*	
  fStepMovemenGridZ=(fStepMovemenGridZ+0.3f)%1;
  fStepMovemenGridX=(fStepMovemenGridX+0.3f)%1;
  fStepMovemenGridY=(fStepMovemenGridY+0.3f)%1;
*/
  fStepMovemenGridZ=(fStepMovemenGridZ+0.3f);
  fStepMovemenGridX=(fStepMovemenGridX+0.3f);
  fStepMovemenGridY=(fStepMovemenGridY+0.3f);
	
/*	//edited by Mike, 20210310
   int iMovementGridZ = iPrevZ-iZ;
   int iMovementGridX = iPrevX-iX;
   int iMovementGridY = iPrevY-iY;
*/
   int iMovementGridZ=0;
   int iMovementGridX=0;
   int iMovementGridY=0;
	
   if (fStepMovemenGridZ>=1) {
   	 iMovementGridZ = iPrevZ-iZ;
	 fStepMovemenGridZ=0;
   }

   if (fStepMovemenGridX>=1) {
   	 iMovementGridX = iPrevX-iX;
	 fStepMovemenGridX=0;
   }

   if (fStepMovemenGridY>=1) {
   	 iMovementGridY = iPrevY-iY;
	 fStepMovemenGridY=0;
   }

	
   //added by Mike, 20210309
   //TO-DO: -reverify: iMovementGridZ, etc value
   std::cout << "iMovementGridZ: " << iMovementGridZ << "\n";
   std::cout << "iMovementGridX: " << iMovementGridX << "\n";
		
   iCurrentLevelMapContainerOffsetZ += iMovementGridZ; 
   iCurrentLevelMapContainerOffsetX += iMovementGridX; 
   iCurrentLevelMapContainerOffsetY += iMovementGridY; 

/* //removed by Mike, 20210310	
	//added by Mike, 20210310	
   if (iMovementGridZ!=0) {
     iCurrentLevelMapContainerOffsetZ += -MAX_Z_AXIS_VIEWPORT/2; 
   }
   if (iMovementGridX!=0) {
	iCurrentLevelMapContainerOffsetX += -MAX_X_AXIS_VIEWPORT/2; 
   }
//   iCurrentLevelMapContainerOffsetY += -MAX_Y_AXIS_VIEWPORT/2; 
*/
	

   std::cout << "iCurrentLevelMapContainerOffsetZ: " << iCurrentLevelMapContainerOffsetZ << "\n";
   std::cout << "iCurrentLevelMapContainerOffsetX: " << iCurrentLevelMapContainerOffsetX << "\n";

	
//		   std::cout << "MAX_INPUT_TEXT_PER_LINE: " << MAX_INPUT_TEXT_PER_LINE << "\n";
	
/*
   iCurrentLevelMapContainerOffsetZ += (iMovementGridZ-MAX_Z_AXIS_VIEWPORT/2); 
   iCurrentLevelMapContainerOffsetX += (iMovementGridX-MAX_X_AXIS_VIEWPORT/2); 
   iCurrentLevelMapContainerOffsetY += (iMovementGridY-MAX_Y_AXIS_VIEWPORT/2); 
*/
/*
   iCurrentLevelMapContainerOffsetZ += (iMovementGridZ-MAX_Z_AXIS_VIEWPORT); 
   iCurrentLevelMapContainerOffsetX += (iMovementGridX-MAX_X_AXIS_VIEWPORT); 
   iCurrentLevelMapContainerOffsetY += (iMovementGridY-MAX_Y_AXIS_VIEWPORT); 
*/	

  //-1 due to start at zero
//  int iRowCount=iCurrentLevelMapContainerOffsetZ-1;
  int iRowCount=iCurrentLevelMapContainerOffsetZ;
/*	
//  int iColumnCount=iCurrentLevelMapContainerOffsetX-1;
  int iColumnCount=iCurrentLevelMapContainerOffsetX;
*/	
	
  int iCurrentLevelMapContainerOffsetMaxViewPortZ=iRowCount+MAX_Z_AXIS_VIEWPORT;
/*  int iCurrentLevelMapContainerOffsetMaxViewPortX=iColumnCount+MAX_X_AXIS_VIEWPORT;
*/	
	
	
   if (iCurrentLevelMapContainerOffsetZ<0) {
//     iCurrentLevelMapContainerOffsetZ=0;
	 iRowCount=0;   
   } 
   else if (iCurrentLevelMapContainerOffsetZ>=MAX_INPUT_TEXT_PER_LINE) {
//     iCurrentLevelMapContainerOffsetZ=MAX_INPUT_TEXT_PER_LINE-1;
	 iRowCount=MAX_INPUT_TEXT_PER_LINE;//-1;   
   } 

/*	
   if (iCurrentLevelMapContainerOffsetX<0) {
	iColumnCount=0;   
   } 
   else if (iCurrentLevelMapContainerOffsetX>=MAX_INPUT_TEXT_PER_LINE) {
iColumnCount=MAX_INPUT_TEXT_PER_LINE;//-1;	   
   } 	
*/	
	
//     iCurrentLevelMapContainerOffsetZ=0;

/*   else if (iCurrentLevelMapContainerOffsetZ>=MAX_Z_AXIS_VIEWPORT) {
     iCurrentLevelMapContainerOffsetZ=MAX_Z_AXIS_VIEWPORT-1;
   } 
*/

/* //removed by Mike, 20210310	
   if (iCurrentLevelMapContainerOffsetX<0) {
     iCurrentLevelMapContainerOffsetX=0;
   } 
////   else if (iCurrentLevelMapContainerOffsetX>=MAX_X_AXIS_VIEWPORT) {
////     iCurrentLevelMapContainerOffsetX=MAX_X_AXIS_VIEWPORT-1;
////   } 
   else if (iCurrentLevelMapContainerOffsetX>=MAX_INPUT_TEXT_PER_LINE) {
     iCurrentLevelMapContainerOffsetX=MAX_INPUT_TEXT_PER_LINE-1;
   } 
*/

	
   //example#1: iPrevZ=-3; iZ=-2;
   //-3 - (-2) = -1
   //-1 < 0, moved forward	
	
   //example#2: iPrevZ=-3; iZ=-2;
   //-3 - (-2) = -1
   //-1 < 0, moved forward	
	
//   if ((iPrevZ-iZ) < 0) { //moved forward
   if (iMovementGridZ < 0) { //moved forward
     std::cout << "forward" << "\n";
//			  std::cout << "iMovementGridZ" << iMovementGridZ <<"\n";	   
   }
   else if (iMovementGridZ == 0) { //no movement in Z-axis
     std::cout << "no movement" << "\n";	   
   }	
   //example: iPrevZ=-2; iZ=-3;
	//-2 - (-3) = 1
	//1 > 0, moved backward		
   else {
     std::cout << "backward" << "\n";	   
//	 iMovementGridZ=iMovementGridZ*-1; //get absolute value, i.e. positive number	   
   }
	
	
/*	//TO-DO: -reverify: this
   if (iMovementGridZ<0) { //if negative value
   	iMovementGridZ=iMovementGridZ*-1; //get absolute value, i.e. positive number
   }
*/
	
/*	
   if (iZ>0) {
   std::cout << "positive forward" << "\n";
	   
//	   iZ=iZ-MAX_Z_AXIS_VIEWPORT;
   }
*/	
	
/* //removed by Mike, 20210306	
	iPrevX=iX;
	iPrevY=iY;
	iPrevZ=iZ;
*/
	
	//added by Mike, 20210306
	//TO-DO: -reverify: iMovementGridZ value
/*  //removed by Mike, 20210306	
   std::cout << "iMovementGridZ: " << iMovementGridZ << "\n";
   std::cout << "iPrevZ: " << iPrevZ << "\n";
*/	
	
	 //edited by Mike, 20210211
//	for (int iRowCount=0; iRowCount<10; iRowCount++) {	
	//edited by Mike, 20210305
//	for (int iRowCount=0; iRowCount<MAX_Z_AXIS_VIEWPORT; iRowCount++) {	
//	for (int iRowCount=fZ; iRowCount<fZ+MAX_Z_AXIS_VIEWPORT; iRowCount++) {	
//	for (int iRowCount=iZ; iRowCount<iZ+MAX_Z_AXIS_VIEWPORT; iRowCount++) {	
//edited by Mike, 20210309
//	for (int iRowCount=0; iRowCount<MAX_Z_AXIS_VIEWPORT; iRowCount++) {		
//edited by Mike, 20210309; edited again by Mike, 20210310
//	for (int iRowCount=0+iCurrentLevelMapContainerOffsetZ; iRowCount<MAX_Z_AXIS_VIEWPORT; iRowCount++) {		
//	for (int iRowCount=0+iCurrentLevelMapContainerOffsetZ; iRowCount<MAX_INPUT_TEXT_PER_LINE; iRowCount++) {		

/* //edited by Mike, 20210310	
	int iCurrentLevelMapContainerOffsetMaxViewPortZ=iCurrentLevelMapContainerOffsetZ+MAX_Z_AXIS_VIEWPORT;
	if (iCurrentLevelMapContainerOffsetMaxViewPortZ>MAX_INPUT_TEXT_PER_LINE) {
		iCurrentLevelMapContainerOffsetMaxViewPortZ=MAX_INPUT_TEXT_PER_LINE;
	}

	int iCurrentLevelMapContainerOffsetMaxViewPortX=iCurrentLevelMapContainerOffsetX+MAX_X_AXIS_VIEWPORT;
	if (iCurrentLevelMapContainerOffsetMaxViewPortX>MAX_INPUT_TEXT_PER_LINE) {
		iCurrentLevelMapContainerOffsetMaxViewPortX=MAX_INPUT_TEXT_PER_LINE;
	}
*/	

/*	//removed by Mike, 20210310
  int iCurrentLevelMapContainerOffsetMaxViewPortZ=iRowCount+MAX_Z_AXIS_VIEWPORT/2;
  int iCurrentLevelMapContainerOffsetMaxViewPortX=iColumnCount+MAX_X_AXIS_VIEWPORT/2;
*/
	
   if (iCurrentLevelMapContainerOffsetMaxViewPortZ<0) {
//     iCurrentLevelMapContainerOffsetZ=0;
	 iCurrentLevelMapContainerOffsetMaxViewPortZ=0;   
   } 
   else if (iCurrentLevelMapContainerOffsetMaxViewPortZ>=MAX_INPUT_TEXT_PER_LINE) {
//     iCurrentLevelMapContainerOffsetZ=MAX_INPUT_TEXT_PER_LINE-1;
	 iCurrentLevelMapContainerOffsetMaxViewPortZ=MAX_INPUT_TEXT_PER_LINE-1;   
   } 

/*	
   if (iCurrentLevelMapContainerOffsetMaxViewPortX<0) {
	 iCurrentLevelMapContainerOffsetMaxViewPortX=0;   
   } 
   else if (iCurrentLevelMapContainerOffsetMaxViewPortX>=MAX_INPUT_TEXT_PER_LINE) {
	 iCurrentLevelMapContainerOffsetMaxViewPortX=MAX_INPUT_TEXT_PER_LINE-1;	   
   } 		
*/	

   std::cout << "iCurrentLevelMapContainerOffsetMaxViewPortZ: " << iCurrentLevelMapContainerOffsetMaxViewPortZ << "\n";
//   std::cout << "iCurrentLevelMapContainerOffsetMaxViewPortX: " << iCurrentLevelMapContainerOffsetMaxViewPortX << "\n";

	
//	   std::cout << "DITO iRowCount: " << iRowCount << "\n";

//	iRowCount=iRowCount+30;
		
	//edited by Mike, 20210310
//	for (int iRowCount=0+iCurrentLevelMapContainerOffsetZ; iRowCount<iCurrentLevelMapContainerOffsetMaxViewPortZ; iRowCount++) {		
	for (;iRowCount<iCurrentLevelMapContainerOffsetMaxViewPortZ; iRowCount++) {		

//	for (int iRowCount=0; iRowCount<MAX_INPUT_TEXT_PER_LINE; iRowCount++) {		
	
/*		
   if (iCurrentLevelMapContainerOffsetZ<0) {
     iCurrentLevelMapContainerOffsetZ=0;
   } 
   else if (iCurrentLevelMapContainerOffsetZ>=MAX_INPUT_TEXT_PER_LINE) {
     iCurrentLevelMapContainerOffsetZ=MAX_INPUT_TEXT_PER_LINE-1;
   } 
*/

/*		
		//added by Mike, 20210305
		if (iMovementGridZ+iRowCount<0) {
//			iMovementGridZ=0;
			iMovementGridZ=0;
			iRowCount=0;			
		}
*/

/*		
		//added by Mike, 20210305
		if (iMovementGridZ+iRowCount<0) {
//			iMovementGridZ=0;
			iMovementGridZ=0;
			iRowCount=0;	
			
			iPrevZ=iMovementGridZ;
			
			
   std::cout << "DITO" << "\n";
			
		}
		//added by Mike, 20210306
		else if (iMovementGridZ+iRowCount>100) { //TO-DO: -add: auto-set max 
			iMovementGridZ=0;
			iRowCount=99;			
			iPrevZ=iRowCount;			
		}
*/		
/*  //removed by Mike, 20210306			
   std::cout << "HALLO: iMovementGridZ+iRowCount: " <<  iMovementGridZ << "+" << iRowCount << "=" << iMovementGridZ+iRowCount << "\n";
*/		
	
	 //edited by Mike, 20210211
//		for (int iColumnCount=0; iColumnCount<10; iColumnCount++) {		
	//edited by Mike, 20210305		
//		for (int iColumnCount=0; iColumnCount<MAX_X_AXIS_VIEWPORT; iColumnCount++) {					
//		for (int iColumnCount=fX; iColumnCount<fX+MAX_X_AXIS_VIEWPORT; iColumnCount++) {								
//		for (int iColumnCount=iX; iColumnCount<iX+MAX_X_AXIS_VIEWPORT; iColumnCount++) {								
//edited by Mike, 20210309
//		for (int iColumnCount=0; iColumnCount<MAX_X_AXIS_VIEWPORT; iColumnCount++) {			
//edited by Mike, 20210309
//		for (int iColumnCount=0+iCurrentLevelMapContainerOffsetX; iColumnCount<MAX_X_AXIS_VIEWPORT; iColumnCount++) {
//edited by Mike, 20210310
//		for (int iColumnCount=0+iCurrentLevelMapContainerOffsetX; iColumnCount<MAX_INPUT_TEXT_PER_LINE; iColumnCount++) {

//     		  std::cout << "iRowCount" << iRowCount <<"\n";
		

		//added by Mike, 202103010
//  int iColumnCount=iCurrentLevelMapContainerOffsetX-1;	
  int iColumnCount=iCurrentLevelMapContainerOffsetX;	
		int iCurrentLevelMapContainerOffsetMaxViewPortX=iColumnCount+MAX_X_AXIS_VIEWPORT;
	
   if (iCurrentLevelMapContainerOffsetX<0) {
	 iColumnCount=0;   
   } 
   else if (iCurrentLevelMapContainerOffsetX>=MAX_INPUT_TEXT_PER_LINE) {
	 iColumnCount=MAX_INPUT_TEXT_PER_LINE-1;
   } 	
		
		
		
		
//edited by Mike, 20210310		
//		for (int iColumnCount=0+iCurrentLevelMapContainerOffsetX; iColumnCount<(iCurrentLevelMapContainerOffsetX+MAX_INPUT_TEXT_PER_LINE); iColumnCount++) {
	//edited by Mike, 20210310
//		for (int iColumnCount=0+iCurrentLevelMapContainerOffsetX; iColumnCount<iCurrentLevelMapContainerOffsetMaxViewPortX; iColumnCount++) {
		for (;iColumnCount<iCurrentLevelMapContainerOffsetMaxViewPortX; iColumnCount++) {

					
//				printf("%s",sCurrentLevelMapContainer[iRowCount][iColumnCount]);

			//if (sCurrentLevelMapContainer[iRowCount][iColumnCount]=="G") {
//			  if (strcmp(sCurrentLevelMapContainer[iRowCount][iColumnCount],"G") != 0) {
			  //Reference: http://www.cplusplus.com/reference/string/string/compare/;
			  //last accessed: 20210210
			  //note: quotation marks
			  //edited by Mike, 20210305
//			  if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("\"G\"") == 0) { //TRUE			
//			  if (sCurrentLevelMapContainer[fX+iRowCount][fZ+iColumnCount].compare("\"G\"") == 0) { //TRUE
//			  if (sCurrentLevelMapContainer[iZ+iRowCount][iX+iColumnCount].compare("\"G\"") == 0) { //TRUE
/*
			  std::cout << "iMovementGridZ" << iMovementGridZ <<"\n";
>     		  std::cout << "iRowCount" << iRowCount <<"\n";
     		  std::cout << "iMovementGridZ+iRowCount" << iMovementGridZ+iRowCount <<"\n";
*/			

//			std::cout << "LOOB iRowCount" << iRowCount <<"\n";

			//edited by Mike, 20210306
//			  if (sCurrentLevelMapContainer[iMovementGridZ+iRowCount][iMovementGridX+iColumnCount].compare("\"G\"") == 0) { //TRUE
//			  if (sCurrentLevelMapContainer[iZ+iRowCount][iX+iColumnCount].compare("\"G\"") == 0) { //TRUE

//edited by Mike, 20210308
//			  if (sCurrentLevelMapContainer[iZ][iX].compare("\"G\"") == 0) { //TRUE
//edited by Mike, 20210308
//			  if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("\"G\"") == 0) { //TRUE
//edited by Mike, 20210309
//MAX_Z_AXIS_VIEWPORT
//			  if (sCurrentLevelMapContainer[iTotalMovementGridZ+iRowCount][iTotalMovementGridX+iColumnCount].compare("\"G\"") == 0) { //TRUE
//			  if (sCurrentLevelMapContainer[40+iRowCount][iTotalMovementGridX+iColumnCount].compare("\"G\"") == 0) { //TRUE
//			  if (sCurrentLevelMapContainer[40+iRowCount][iColumnCount].compare("\"G\"") == 0) { //TRUE
//			  if (sCurrentLevelMapContainer[40+iRowCount][10].compare("\"G\"") == 0) { //TRUE
//edited by Mike, 20210309
//			  if (sCurrentLevelMapContainer[iCurrentLevelMapContainerOffsetZ+iRowCount][iCurrentLevelMapContainerOffsetX+iColumnCount].compare("\"G\"") == 0) { //TRUE

//			std::cout << "iRowCount:" << iRowCount << "iColumnCount:" << iColumnCount << "\n";

			if (sCurrentLevelMapContainer[iRowCount][iColumnCount].compare("\"G\"") == 0) { //TRUE
			//start at 0 in double array container 
//		    if (sCurrentLevelMapContainer[99][10].compare("\"G\"") == 0) { //TRUE
//			
//				  			  std::cout << "DITO" <<"\n";

//				  printf("DITO");
				
			    //Grass
				sprintf(tempText,"G");
			
				//added by Mike, 20201124
			    glColor3f(0.14f, 0.68f, 0.06f); // Green

				//added by Mike, 20201124
				//execute this when using solid colors
				//for computer to not draw borders
				glBindTexture( GL_TEXTURE_2D, 0 );
				
				//edited by Mike, 20210305
//				draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
//				draw_level(fX+fGridSquareWidth*iColumnCount, fY+0.0f, fZ+fGridSquareHeight*iRowCount, tempText);
//				draw_level(iX+fGridSquareWidth*iColumnCount, iY+0.0f, iZ+fGridSquareHeight*iRowCount, tempText);
//				draw_level(iMovementGridX+fGridSquareWidth*iColumnCount, iMovementGridY+0.0f, iMovementGridZ+fGridSquareHeight*iRowCount, tempText);
//				draw_level(iX+fGridSquareWidth*iColumnCount, iY+0.0f, iZ+fGridSquareHeight*iRowCount, tempText);
//				draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);


//				draw_level(iMovementGridX+fGridSquareWidth*iColumnCount, iMovementGridY+0.0f, iMovementGridZ+fGridSquareHeight*iRowCount, tempText);
//				draw_level(iTotalMovementGridX+fGridSquareWidth*iColumnCount, iTotalMovementGridY+0.0f, iTotalMovementGridZ+fGridSquareHeight*iRowCount, tempText);
				
//edited by Mike, 20210309
//				draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
//				draw_level(fGridSquareWidth*iColumnCount, 0.0f, fZ+fGridSquareHeight*iRowCount, tempText);
//set position
//				draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*40+fGridSquareHeight*iRowCount, tempText);
				draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);

//				draw_level(fGridSquareWidth*10, 0.0f, fGridSquareHeight*99, tempText);
//				draw_level(fGridSquareWidth*5, 0.0f, fGridSquareHeight*5, tempText);
				
			}			
		}
	}

/*	
		//added by Mike, 20210305
		if (iMovementGridZ+iRowCount<0) {
//			iMovementGridZ=0;
			iMovementGridZ=0;
			iRowCount=0;	
			
			iPrevZ=iMovementGridZ;
			
			
   std::cout << "DITO" << "\n";
			
		}
		//added by Mike, 20210306
		else if (iMovementGridZ+iRowCount>100) { //TO-DO: -add: auto-set max 
			iMovementGridZ=0;
			iRowCount=99;			
			iPrevZ=iRowCount;			
		}
*/	

	//added by Mike, 20210306; edited by Mike, 20210308	
	iPrevX=iX;
	iPrevY=iY;
	iPrevZ=iZ;

/*	
	//added by Mike, 20210308
	fPrevX=fX;
	fPrevY=fY;
	fPrevZ=fZ;
*/	


/* //removed by Mike, 20210208	
	for (int iRowCount=0; iRowCount<=iRowCountMax; iRowCount++) {	
	 	for (int iColumnCount=0; iColumnCount<=iColumnCountMax; iColumnCount++) {		
			//added by Mike, 20201124
			//execute this when using solid colors
			//for computer to not draw borders
			glBindTexture( GL_TEXTURE_2D, 0 );
			draw_level(fGridSquareWidth*iColumnCount, 0.0f, fGridSquareHeight*iRowCount, tempText);
		}
	}
*/
}

void Level::setupLevel(int myLevelTextureObject)
{
/*	//removed by Mike, 20210208
	//added by Mike, 20210208
//	UsbongUtils myUsbongUtils = UsbongUtils();
	myUsbongUtils = new UsbongUtils();
//	myUsbongUtils->read("inputHalimbawa.txt");
//	char* sOutput = myUsbongUtils->read("inputLevel1.csv"); 	
//	char sOutput[100] = myUsbongUtils->read("inputLevel1.csv"); 	
	
	//TO-DO: -add: read command in Level.cpp 
//	myUsbongUtils->read("inputLevel1.csv"); 	
*/	
	//added by Mike, 20210208
	read("inputLevel1.csv");

	//added by Mike, 20210308
/*	//edited by Mike, 20210310	
	iPrevZ=0;
	iPrevY=0;
	iPrevX=0;
*/	//start values
	//+12 for robotShip start position, i.e. 3*4
/*	iPrevZ=-11+12; //11;
	iPrevY=0;
	iPrevX=-11+12;//-11;
*/
	//viewport
/*	
	iPrevZ=-11-MAX_Z_AXIS_VIEWPORT/2; //11;
	iPrevY=0;
	iPrevX=-11-MAX_X_AXIS_VIEWPORT/2;//-11;
*/
	iPrevZ=-MAX_Z_AXIS_VIEWPORT/2-11;
	iPrevY=0;
	iPrevX=-MAX_X_AXIS_VIEWPORT/2-11;
	
	iTotalMovementGridZ=0;
    iTotalMovementGridX=0;
    iTotalMovementGridY=0;	

	//added by Mike, 20210309
	iCurrentLevelMapContainerOffsetX=0;
	iCurrentLevelMapContainerOffsetY=0;
	iCurrentLevelMapContainerOffsetZ=0;
	
	//TO-DO: -add: in input file, max size of x, y, and z axes
	//TO-DO: -add: auto-update iCurrentLevelMapContainer

//	printf("%s\n",sOutput);
			
	//removed by Mike, 20201010
	//due to blank output
    //glEnable(GL_DEPTH_TEST);
	
	//edited by Mike, 20201122
    /* select texture 2 */
    glBindTexture(GL_TEXTURE_2D, myLevelTextureObject);

    /* create OpenGL texture out of targa file */
    //TO-DO: -reverify: cube face using font texture
    //edited by Mike, 20201119
//    load_tga("textures/font.tga");
	//TO-DO: -reverify: if level.tga is loaded
    load_tga("textures/level.tga");
    
	/* set texture parameters */
	//Note: GL_CLAMP: each texture had a 1-pixel border
	//Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes;
	//last accessed: 20201123
/*	//edited by Mike, 20201123
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
*/

	//edited by Mike, 20201124
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

/*
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
*/

//Reference: https://www.opengl.org/archives/resources/code/samples/sig99/advanced99/notes/node64.html;
//last accessed: 20201124

//TO-DO: -reverify: this due to computer still draws border at the edges
/*
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
GLfloat color[4]={1,1,1,1};
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
*/

/*
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
*/
/*    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
*/

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


/*
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0); 
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0); 
*/

/*
float colour[4] = {1.0f, 0.0f, 1.0f, 1.0f};
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, colour);
*/



    /* unselect texture myLevelTextureObject */
    glBindTexture(GL_TEXTURE_2D, 0);

/*	//removed by Mike, 20201123
    // setup alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    // set background color to bluish // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // unselect texture myLevelTextureObject
    glBindTexture(GL_TEXTURE_2D, 0);
    // setup alpha blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
*/
	//removed by Mike, 20201012
    // set background color to bluish to demonstrate font transparency
//    glClearColor(0.0f, 0.0f, 0.25f, 1.0f); // to demonstrate font transparency
//    glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // to demonstrate font transparency

}

//added by Mike, 20210208
/* //previous; removed by Mike, 20210208
void Level::read(char *inputFilename) {
	int c;
	FILE *file;
	
	//TO-DO: update: this	
	
	//noted by Mike, 20201210
	//note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
	//I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
	//where memory leaks = not deallocated storage in memory, albeit not used by software application
	//identifying not deallocated storage in memory becomes more difficult with increasing use
	char input[60]; //max size
	strcpy(input, "input/");
	strcat(input, inputFilename); //already includes .txt
//	strcat(input,".txt");
	
//	printf("dito: %s",input);
//	file = fopen("input/"+inputFilename, "r"); //.txt file
//	file = fopen("input/inputHalimbawa.txt", "r"); //.txt file
	file = fopen(input, "r"); //.txt file
	if (file) {
		while ((c = getc(file)) != EOF) {
			putchar(c);
		}
		fclose(file);
	}	
}
*/

//added by Mike, 20210208
void Level::read(char *inputFilename) {
	int c;
	FILE *file;
	
	//TO-DO: update: this		
//	char** iCurrentLevelMapContainer = new char[100][100];	
	int iRowCount=0;
	int iColumnCount=0;

	//set to 0 value
	//10;100
/*	//edited by Mike, 20210211
	for (iRowCount=0; iRowCount<10; iRowCount++) {	
		for (iColumnCount=0; iColumnCount<10; iColumnCount++) {		
*/
/*	//edited by Mike, 20210305
	for (iRowCount=0; iRowCount<MAX_Z_AXIS_VIEWPORT; iRowCount++) {	
		for (iColumnCount=0; iColumnCount<MAX_X_AXIS_VIEWPORT; iColumnCount++) {		
	 		sCurrentLevelMapContainer[iRowCount][iColumnCount]=(char*)"-1";//'G';
		}
	}
*/
	for (iRowCount=0; iRowCount<100; iRowCount++) {	
		for (iColumnCount=0; iColumnCount<100; iColumnCount++) {		
	 		sCurrentLevelMapContainer[iRowCount][iColumnCount]=(char*)"-1";//'G';
		}
	}

//added by Mike, 20210309
/*
	for (iRowCount=40; iRowCount<60; iRowCount++) {	
	 	sCurrentLevelMapContainer[iRowCount][2]=(char*)"\"G\"";//'G';
	}
	for (iRowCount=60; iRowCount<100; iRowCount++) {	
	 	sCurrentLevelMapContainer[iRowCount][4]=(char*)"\"G\"";//'G';
	}
*/	
	

	iRowCount=0;
	iColumnCount=0;
				
	//noted by Mike, 20201210
	//note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
	//I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
	//where memory leaks = not deallocated storage in memory, albeit not used by software application
	//identifying not deallocated storage in memory becomes more difficult with increasing use
	char input[MAX_INPUT_TEXT_PER_LINE]; //max size
	char inputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
	char tempInputTextLine[MAX_INPUT_TEXT_PER_LINE]; //max size
	
	strcpy(input, "input/");
	strcat(input, inputFilename); //already includes .txt
//	strcat(input,".txt");
	
//	printf("dito: %s",input);

//	file = fopen("input/"+inputFilename, "r"); //.txt file
//	file = fopen("input/inputHalimbawa.txt", "r"); //.txt file
	file = fopen(input, "r"); //.txt file

	//TO-DO: -reverify: tile positions
	int iCount=0;
	
	if (file) {
		//edited by Mike, 20210210
//		while ((c = getc(file)) != EOF) {
		while (fgets (input, MAX_INPUT_TEXT_PER_LINE, file)) { /* read each line of input */			
//	putchar(c);
			
/*	//removed by Mike, 20210210
			char sRow[2] = {(char)c};
*/			
			//delimited using new line
/*			char *chRow = strtok(sRow, "\n");
*/
			sscanf (input, "%s", inputTextLine);
         
			
//			iCount=0;
	//input text per line			
//			printf("%i;\n",iCount);
			printf("%i;",iCount);
			iCount=iCount+1;
						
				//added by Mike, 20210208
				iColumnCount=0;
	
				//removed by Mike, 20210210
/*				
	//			char s[2] = {0};
	//			*s = c;
				//edited by Mike, 20210209
//				char s[2] = {c};
//				char s[2] = {itoa(c)};
				char s[2] = {(char)c};
				
				//delimited using comma
				char *ch = strtok(s, ",");
*/					
			strcpy(tempInputTextLine,inputTextLine);
	
			//note: add "-1" for empty
			//otherwise, comma as column is skipped
			char *ch = strtok(tempInputTextLine, ",");
				
			while (ch != NULL) {	
//				printf("%i,",iColumnCount);
					
				//TO-DO: use String, instead of char
				//TO-DO: -reverify: output due to "G" not put in container
//				sCurrentLevelMapContainer[iRowCount][iColumnCount]=&ch;
				sCurrentLevelMapContainer[iRowCount][iColumnCount]=ch;

/*	//edited by Mike, 20210211		
				printf("%s:",ch);
				printf("%i,",iColumnCount);
*/
				printf("%i:",iColumnCount);
				printf("%s,",ch);
				
				iColumnCount=iColumnCount+1;
				  ch = strtok(NULL, ",");
			}			

			if (iRowCount<100) {
				iRowCount=iRowCount+1;
			}
			else {
				iRowCount=0;
			}
			
			printf("\n");			
		}
		fclose(file);
	}	

/*	
	for (iRowCount=0; iRowCount<100; iRowCount++) {	
	 	for (iColumnCount=0; iColumnCount<100; iColumnCount++) {		
	 		printf("%s",sCurrentLevelMapContainer[iRowCount][iColumnCount]);
		}
			printf("\n");			
	}	
*/
	
		
}