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
 * @date updated: 20200930
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//TO-DO: -update: this
 
//#include "CTargaImage.h"
#include "OpenGLCanvas.h"
#include "MyDynamicObject.h"

//#define STANDING_STATE 0
//#define WALKING_STATE 1

const int INITIALIZING_STATE = 0;
const int MOVING_STATE = 1;
const int IN_TITLE_STATE =2;
const int DYING_STATE =3;

class RobotShip: public MyDynamicObject
{
private:	
	int currentState;
	Sound *sound;
	SoundClip *zing;
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
    //int currentFacingState;    
/*
    CTargaImage *myBodyTexture;
   	unsigned int myBodyTextureObject;

    CTargaImage *myHeadTexture;
   	unsigned int myHeadTextureObject;
*/
    GLint tricount;
    GLint isMovingForward;

    GLboolean test_pow2(GLushort i);
    void load_tga(char *filename);

    //draw texture
    //bool loadTexture(CTargaImage *myTexture, const char *filename, unsigned int *myTextureObject);
    void setup();

	// draws a unit cube
	//void drawCube(float xPos, float yPos, float zPos);

    // draw a unit triangle, Mike Dec. 19, 2006
    //void drawTriangle(float xPos, float yPos, float zPos);
    //void drawTriangledCube(float xPos, float yPos, float zPos);
    
public:
	RobotShip();
	~RobotShip();
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
  
	// draws the entire robot
	//void drawRobot(float xPos, float yPos, float zPos);
    void drawRobotShip();
//    void drawValkyrie();
        
	// updates the robot data
	void update(float dt);
	
	// changes the robot's state
	void changeState(int s);
	
	void move(int key);
	
	void setOpenGLCanvas(OpenGLCanvas* c);
    virtual void hitBy(MyDynamicObject* mdo);
    
    void reset();
    int getState();
};
