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
 * @date created: 20201118
 * @date updated: 20201125
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
//#include <string.h>
#include <string>

//added by Mike, 20201011
#include <iostream>

//added by Mike, 20201118
#include "Level.h"

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

void Level::setupLevel(int myLevelTextureObject)
{
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