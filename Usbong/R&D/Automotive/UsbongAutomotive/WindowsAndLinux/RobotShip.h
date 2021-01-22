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
 * @date updated: 20210121
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: this

//added by Mike, 20201130 
#include "CTargaImage.h"

#include "OpenGLCanvas.h"
#include "MyDynamicObject.h"

//added by Mike, 20201019
#include "PolygonUtils.h"

//added by Mike, 20201226
#define TRUE 1
#define FALSE 0

/* //edited by Mike, 20201207
//added by Mike, 20201201
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

const int INITIALIZING_STATE = 0;
const int MOVING_STATE = 1;
const int IN_TITLE_STATE = 2;
const int DYING_STATE = 3;

//added by Mike, 20201130
//TO-DO: -add: diagonal
#define FACING_UP 0
#define FACING_DOWN 1
#define FACING_LEFT 2
#define FACING_RIGHT 3
*/

class RobotShip: public MyDynamicObject
{
private:	
	int currentState;
/*	//removed by Mike, 20201001
	Sound *sound;
	SoundClip *zing;
*/
	
	//added by Mike, 20201201
	int currentMovingState;
	
/*
    float myXPos;
    float myYPos;
    float myZPos;
*/    
    float stepX;
    float stepY;
    float stepZ;
/*    
    float myWidthX;
    float myWidthZ;
    float myHeightY;
*/    
    OpenGLCanvas *myOpenGLCanvas;

    //float boundary;

//    float rotationAngle;
    float rotationAngleRad;
    float rotationStep;
    
    float thrust;
    float thrustMax;
    float xAccel;
    float yAccel;
    float xVel;
    float yVel;
    
    float maxXVel;
    float maxYVel;    
    
    int invincibleCounter;
    
    unsigned int myDeathAnimationImg1,
                 myDeathAnimationImg2,
                 myDeathAnimationImg3,
                 myDeathAnimationImg4,
                 myDeathAnimationImg5;
    int currentDeathFrame;
    
    //int previousFacingState;
	//added by Mike, 20201201    
    int currentFacingState;    

	//added by Mike, 20210111
    int iFiringBeamCount;    

	//added by Mike, 20201130
    CTargaImage *myBodyTexture;
   	unsigned int myBodyTextureObject;

    CTargaImage *myHeadTexture;
   	unsigned int myHeadTextureObject;

	//added by Mike, 20201201
	char legStates[2];	
	char armStates[2];

	float legAngles[2];
	float armAngles[2];
	
	//added by Mike, 20201225
	bool bIsFiringBeam;
	bool bHasPressedADirectionalKey; //added by Mike, 20201226
	
	//added by Mike, 20210111
	bool bIsExecutingPunch,	
		 bIsExecutingDefend; //added by Mike, 20210112; edited by Mike, 20210121

    GLint tricount;
    GLint isMovingForward;

    GLboolean test_pow2(GLushort i);
    void load_tga(char *filename);
	
    //draw texture
	//added by Mike, 20201130
    bool loadTexture(CTargaImage *myTexture, const char *filename, unsigned int *myTextureObject);
    void setup();

	// draws a unit cube
	//void drawCube(float xPos, float yPos, float zPos);

	//added by Mike, 20201130
    // draw a unit triangle, Mike Dec. 19, 2006
    void drawTriangle(float xPos, float yPos, float zPos);
    void drawTriangledCube(float xPos, float yPos, float zPos);

	//added by Mike, 20201130
	// methods to draw the parts of the robot
	void drawUpperArm(float xPos, float yPos, float zPos);
	void drawLowerArm(float xPos, float yPos, float zPos);
	//removed by Mike, 20201130
//	void drawAntenna(float xPos, float yPos, float zPos);
	void drawHead(float xPos, float yPos, float zPos);
	void drawBody(float xPos, float yPos, float zPos);
	void drawUpperLeg(float xPos, float yPos, float zPos);
	void drawLowerLeg(float xPos, float yPos, float zPos);
	void drawFoot(float xPos, float yPos, float zPos);
    
    //added by Mike, 20210107
	void drawWeapon(float xPos, float yPos, float zPos);

public:
	//edited by Mike, 20201115 
	//RobotShip();
    RobotShip(float xPos, float yPos, float zPos,int windowWidth,int windowHeight);

	~RobotShip();

	//added by Mike, 20201226
	//note: we classify this container as public;
	//otherwise; computer notifies us of error when we update value inside container
   	//edited by Mike, 20201227
   	//TO-DO: -update: this to include diagonal directional movement
	//int myKeysDown[4];
	//edited by Mike, 20210102
	//int myKeysDown[10]; //note: does not include KEY_J, KEY_L, KEY_I, KEY_K,
	int myKeysDown[14]; //note: includes KEY_J, KEY_L, KEY_I, KEY_K,
	
	//virtual ~Robot();
    float rotationAngle;	

    virtual float getX()
    {
       return myXPos;
    }
    virtual float getY()
    {
       return myYPos;
    }
    virtual float getZ()
    {
       return myZPos;
    }
    virtual float getWidth()
    {
       return myWidth;
    }
    virtual float getHeight()
    {
       return myHeight;
    }
    //int STANDING_STATE;
    //int WALKING_STATE;
    float getRotationAngle(){
      return rotationAngle;
    }
  	
    float* getXYZPos();
    
    //added by Mike, 20201230
    float getCurrentFacingState() {
    	return currentFacingState;
	}

    //added by Mike, 20210102; edited by Mike, 20210106
    void setCurrentFacingState(int iNewFacingState) {
    	currentFacingState = iNewFacingState;
	}

    //added by Mike, 20210111
//    bool getIsExcutingPunchDefense() {
    bool getIsExecuteWithWeaponReady() {
    	if (bIsExecutingPunch) {
    		return false;
		}
		//edited by Mike, 20210121
		else if (bIsExecutingDefend) {
    		return false;
		}
    	return true;
	}
    
    //added by Mike, 20201213
    virtual void draw() {
    	drawRobotShip();
    }
  
	// draws the entire robot
	//void drawRobot(float xPos, float yPos, float zPos);
    void drawRobotShip();
//    void drawValkyrie();
	//added by Mike, 20201001
	//TO-DO: -add: in ModelPool.cpp
	void drawModelRobotShip();
        
	// updates the robot data
	void update(float dt);
	
	// changes the robot's state
	void changeState(int s);
	
	void move(int key);
	
	//added by Mike, 20201226
	void keyDown(int keyCode);	
	void keyUp(int keyCode);	
	
	void setOpenGLCanvas(OpenGLCanvas* c);
    virtual void hitBy(MyDynamicObject* mdo);

	//added by Mike, 20201016
    virtual void destroy();
    
    void reset();
    int getState();
};
