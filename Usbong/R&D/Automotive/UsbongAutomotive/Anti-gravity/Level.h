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
 * @date updated: 20210211
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
#include <stdlib.h> 

//edited by Mike, 20201011
//#include <string.h>
#include <string>

//added by Mike, 20201120
#include "PolygonUtils.h"

/*	//removed by Mike, 20201210; used in Level.cpp
//added by Mike, 20201210
#include "UsbongUtils.h"
*/

//added by Mike, 20201123
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE_BASE_LEVEL 0x813C 
#define GL_TEXTURE_MAX_LEVEL 0x813D
//added by Mike, 20201124
#define GL_CLAMP_TO_BORDER 0x812D

//added by Mike, 20210210
#define MAX_INPUT_TEXT_PER_LINE 60

//added by Mike, 20210211
#define MAX_X_AXIS_VIEWPORT 60
#define MAX_Y_AXIS_VIEWPORT 60
#define MAX_Z_AXIS_VIEWPORT 60


//added by Mike, 20201210
class UsbongUtils;

class Level
{
private:
	//added by Mike, 20201210
	//TO-DO: -reverify: immediately use UsbongUtils without need to create instance
    UsbongUtils *myUsbongUtils;

	//added by Mike, 20210208
//	int[100][100] iCurrentLevelMapContainer; //TO-DO: -add: auto-update max size 
	//int** iCurrentLevelMapContainer; //TO-DO: -add: auto-update max size 
//	char** iCurrentLevelMapContainer; //TO-DO: -add: auto-update max size 
//	char[100][100] cCurrentLevelMapContainer; //TO-DO: -add: auto-update max size 
//TO-DO: -update: "c" to "s"
//	char* cCurrentLevelMapContainer[100][100]; //TO-DO: -add: auto-update max size 
	std::string cCurrentLevelMapContainer[100][100]; //TO-DO: -add: auto-update max size 

	GLboolean test_pow2(GLushort i);
	void load_tga(char *filename);

	//added by Mike, 20210208
	void read(char *inputFilename);
	
public: 
	void setupLevel(int myLevelTextureObject);
	
	//added by Mike, 20210211
	int getMaxXAxisViewport() {
		return MAX_X_AXIS_VIEWPORT;
	}
	int getMaxYAxisViewport() {
		return MAX_Y_AXIS_VIEWPORT; 
	}
	int getMaxZAxisViewport() {
		return MAX_Z_AXIS_VIEWPORT; 
	}
	
	/*	//removed by Mike, 2020118
	void draw_string(GLfloat x, GLfloat y, GLfloat z, char *string);
	void draw_char(GLfloat x, GLfloat y, GLfloat z, char c);
	*/
	//TO-DO: -update: this
	void draw_char(GLfloat x, GLfloat y, GLfloat z, char c);
	void draw_level(GLfloat x, GLfloat y, GLfloat z, char *string);	
	
	//added by Mike, 20210208
	void drawLevelMapInViewPort(GLfloat fX, GLfloat fY, GLfloat fZ, GLfloat fXSize, GLfloat fYSize, GLfloat fZSize);	

};
