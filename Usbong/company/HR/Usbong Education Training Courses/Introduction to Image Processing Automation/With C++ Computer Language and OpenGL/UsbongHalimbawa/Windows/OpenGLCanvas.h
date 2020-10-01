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
 * @date created: 20200929
 * @date updated: 20201001
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: "Canvas" to "Engine"?
//TO-DO: -update: this

#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <windows.h> //Windows Machine

//#include "CTargaImage.h"

/* //removed by Mike, 20200929
#include "MyDynamicObject.h"

#include "Sound.h"
*/

#include <stdio.h>


#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0
#define TRUE 1
#define FALSE 0

#define FONT_TEXTURE 2

#define MAX_ENEMY 2
#define MAX_BEAMS 5
#define MAX_ASTEROID 28 //groups of 3, therefore 4 groups, plus inner groupings
#define MAX_LIFE 3
#define REQUIRED_POINTS_FOR_BONUS 30000 //5000


#define MAX 1026 //buffer

#define TITLE_SCREEN 0
#define CONTROLS_SCREEN 1
#define GAME_SCREEN 2
#define GAMEOVER_SCREEN 3
#define HIGHSCORE_SCREEN 4


#define ROBOTSHIP_INITIALIZING_STATE 0

class RobotShip;
class Enemy;
class Beam;
class Asteroid;

class OpenGLCanvas
{
    private:
    	RobotShip *myRobotShip,
    	          *myRobotShipPlayer2;

        //Enemy *myEnemy[MAX_ENEMY];
        Enemy *myEnemy;
        Beam *myBeam[MAX_BEAMS];
        Asteroid *myAsteroid[MAX_ASTEROID];
//        Asteroid *myAsteroid;

       	char *infile;//= "Patches1.txt";		
        char *outfile;
       	FILE *in;
        FILE *out;
        char buffer[MAX];

    	float rotationAngle;
    
    	int myWindowWidth;
    	int myWindowHeight;
    	
   		int myKeysDown[4];	
   		float rotationSpeed;
    
        int myRepaintCounter;
        int myRepaintDelay;
       	
   	    char tempText[50];
        int score,
            rest,
            restPlayer2,
            missiles,
            highScore,
            numOfAsteroidsLeft,
            currFrame,
            keyPressCounter,
            scoreBeforeBonus;
        bool isTwoPlayers;
       
       	//unsigned int myFontTextureObject;
               
        unsigned int myFontListBase;	    

//removed by Mike, 20200930, due to Linux Machine
//        HDC hDC;

        //CTargaImage *myBackground,
        //            *myFont;
       	unsigned int currTextureBackground,
       	             myTextureObjectFont,
       	             titleBackground,
       	             gameBackground;
    	bool loadBackground();
    	bool setupProjection();
    	//removed by Mike, 20200930
    	//void drawPlane();
    	void drawGrid();
    	
    	void gameReset();
    	void resetDynamicObjects();
    	
        GLboolean test_pow2(GLushort i);
        void load_tga(char *filename);

/*
        //methods to generate bitmap texts
        unsigned int createBitmapFont(char *fontName, int fontSize);
        void renderFont(int xPos, int yPos, unsigned int base, char *str);
	    void releaseFont(unsigned int base);
*/        
    public:
    	OpenGLCanvas();
    	~OpenGLCanvas();
    	//virtual ~CGfxOpenGL();
    	
/*		//removed by Mike, 20200929
        Sound *sound;
        SoundClip *beam, *valkyrie, *explosion, *zing, *thrust, *rotate, *bonus, *title;
*/        
        int currentState;

    	bool init();
    	bool shutdown();

   		void keyDown(int keyCode);
	    void keyUp(int keyCode);
		
    	//void Prepare(float dt);
    	void render();
    	void update();
    	
    	void addScore(int s);
    	void loseLife();
    	void changeState(int s);
};

#endif

