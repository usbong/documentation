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
 * @date created: 20201019
 * @date updated: 20201121
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//TO-DO: -update: this

#include "PolygonUtils.h"
#include <math.h>

//#include <SDL.h>

//edited by Mike, 20201019
#include <GL/gl.h>
#include <GL/glut.h> 
#include <GL/glu.h>

//added by Mike, 20201114; removed by Mike, 20201114
// disable implicit float-double casting
//#pragma warning(disable:4305)

/*
#include <stdio.h>
#include <stdlib.h>
*/

/*	//removed by Mike, 20201019
void drawCube(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
		glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
		glEnd();
	glPopMatrix();
}
*/

void drawTriangle(float xPos, float yPos, float zPos)
{
	glPushMatrix();
		glTranslatef(xPos, yPos, zPos);
        //front
		glBegin(GL_TRIANGLES);
            //glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
            //glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-0.5f, 0.0f, 0.0f);
            //glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.5f, 0.0f, 0.0f);
		glEnd();
		//back
		glBegin(GL_TRIANGLES);
            glVertex3f(0.5f, 0.0f, 0.0f);
            glVertex3f(-0.5f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.5f, 0.0f);
		glEnd();

	glPopMatrix();     	
}

//added by Mike, 20201019
//void drawSquare(float xPos, float yPos, float zPos) {
void drawSquare() {
	//to make anchor/origin/reference point start at top-left
    glTranslatef(0.0f, 0.1f, 0.0f);   
	
	//Reference: https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html;
	//last accessed: 20200928 
   //note: 0.5f = half of the window width or height
   // Draw a Red 1x1 Square centered at origin
   //TO-DO: -update: this due to output is 1 x 2 box, width x height
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
/*    //edited by Mike, 20201001  
	  glVertex2f(-0.1f, -0.1f);    // x, y
      glVertex2f( 0.1f, -0.1f);
      glVertex2f( 0.1f,  0.1f);
      glVertex2f(-0.1f,  0.1f);
*/      
	  //1x1 square
	  glVertex2f(0.0f, 0.0f);    // x, y
      glVertex2f( 0.0f, -0.1f);
      glVertex2f( 0.1f,  -0.1f);
      glVertex2f(0.1f,  0.0f);
   glEnd();    
}


//Reference: Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
//void CGfxOpenGL::DrawCube(float xPos, float yPos, float zPos)
//void drawCube()
void drawCube(float fSideLength)
{
	glPushMatrix();
	//to make anchor/origin/reference point start at top-left
//		glTranslatef(xPos, yPos, zPos);
		//note: we add 0.2f in x-axis due to vertex locations 
		//of cube's square face not equal with that of drawSquare()
//	    glTranslatef(0.0f, 0.1f, 0.0f);

		//TO-DO: -reverify: this if necessary
		//edited by Mike, 20201116
//	    glTranslatef(0.2f, 0.1f, 0.0f);   
	    glTranslatef(0.0f, fSideLength, 0.0f);   //0.0f, 1.0f, 0.0f
		
		//TO-DO: -update: vertex locations
		
		//added by Mike, 20201114
//		glDepthFunc(GL_ALWAYS);
//		glEnable(GL_DEPTH_TEST);	
		//removed by Mike, 20201114		
/*
		// Draw lines antialiased
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/
		//removed by Mike, 20201114		
		// Draw black wireframe version of geometry
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

/*		//removed by Mike, 20201114
		//added by Mike, 20201114
		glDepthFunc(GL_LEQUAL);

		glLineWidth(2.0f);

		glEnable( GL_POLYGON_OFFSET_FILL );
        glPolygonOffset( 1.0, 1.0 ); //3.0, 1.0 );	
*/		

		glLineWidth(2.0f);
		
		glBegin(GL_QUADS);
/*		
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);	// left face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);	// bottom face
			glVertex3f(0.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);	// back face
			glVertex3f(-1.0f, 0.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(0.0f, -1.0f, -1.0f);
*/
/*			//edited by Mike, 20201023
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -0.1f);
			glVertex3f(-0.1f, 0.0f, -0.1f);
			glVertex3f(-0.1f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-0.1f, 0.0f, 0.0f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, -0.1f);
			glVertex3f(0.0f, 0.0f, -0.1f);
			glVertex3f(-0.1f, 0.0f, 0.0f);	// left face
			glVertex3f(-0.1f, 0.0f, -0.1f);
			glVertex3f(-0.1f, -0.1f, -0.1f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(0.0f, -0.1f, 0.0f);	// bottom face
			glVertex3f(0.0f, -0.1f, -0.1f);
			glVertex3f(-0.1f, -0.1f, -0.1f);
			glVertex3f(-0.1f, -0.1f, 0.0f);
			glVertex3f(0.0f, 0.0f, -0.1f);	// back face
			glVertex3f(-0.1f, 0.0f, -0.1f);
			glVertex3f(-0.1f, -0.1f, -0.1f);
			glVertex3f(0.0f, -0.1f, -0.1f);
*/
			//note: add vertex counter-clockwise
			glVertex3f(0.0f, 0.0f, 0.0f);	// top face
			glVertex3f(0.0f, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, 0.0f);

			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(0.0f, 0.0f, -fSideLength);
			//edited by Mike, 2020114
			//vertices drawn clock-wise
			
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

/*
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

			//edited by Mike, 20201114
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//TO-DO: -reverify: disable BackFaceCulling 
			//+updated: to draw vertices clockwise due to back face not drawn
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//draw vertices clockwise
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

	glPopMatrix();
}

//Reference: Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
//added by Mike, 20201120
void drawCubeWithBlockTexture(float fSideLength, GLfloat tx, GLfloat ty, GLfloat tz, float x, float y, float z)
{
	glPushMatrix();
		//TO-DO: -reverify: cause of cube translation when moving camera	
//		glLineWidth(2.0f);
	    glTranslatef(x, y, z);
	    
		//edited by Mike, 20201121
//	    glTranslatef(fSideLength, 0.0f, fSideLength);
	    glTranslatef(0.0f, 0.0f, fSideLength);
		//added due to inverted z-axis based on position of vertices 
		glRotatef(180, 0.0f, 0.0f, 1.0f);
				
		glBegin(GL_QUADS);
/*
			// top face		
			//note: added vertices counter-clock-wise
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);
*/
			// top face		
	        glTexCoord2f(tx, ty);
			glVertex3f(0.0f, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty);			
			glVertex3f(-fSideLength, 0.0f, 0.0f);

        	glTexCoord2f(tx + 0.078125f, ty + 0.125f);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

			glTexCoord2f(tx, ty + 0.125f);			
			glVertex3f(0.0f, 0.0f, -fSideLength);


			//TO-DO: -update: this
			glVertex3f(0.0f, 0.0f, 0.0f);	// front face
			glVertex3f(-fSideLength, 0.0f, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, 0.0f);

			glVertex3f(0.0f, 0.0f, 0.0f);	// right face
			glVertex3f(0.0f, -fSideLength, 0.0f);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(0.0f, 0.0f, -fSideLength);
			//edited by Mike, 2020114
			//vertices drawn clock-wise
			
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

/*
			glVertex3f(-fSideLength, 0.0f, 0.0f);	// left face
			glVertex3f(-fSideLength, -fSideLength, 0.0f);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
*/
			glVertex3f(0.0f, -fSideLength, 0.0f);	// bottom face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, 0.0f);

			//edited by Mike, 20201114
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//TO-DO: -reverify: disable BackFaceCulling 
			//+updated: to draw vertices clockwise due to back face not drawn
/*			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(-fSideLength, 0.0f, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(0.0f, -fSideLength, -fSideLength);
*/
			//draw vertices clockwise
			glVertex3f(0.0f, 0.0f, -fSideLength);	// back face
			glVertex3f(0.0f, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, -fSideLength, -fSideLength);
			glVertex3f(-fSideLength, 0.0f, -fSideLength);

		glEnd();
		
/*		//removed by Mike, 20201114		
		//added by Mike, 20201114
		glDisable( GL_POLYGON_OFFSET_FILL );
*/

		//added by Mike, 20201114; removed by Mike, 2020114
//		glDepthFunc(GL_LESS);

	glPopMatrix();
}
