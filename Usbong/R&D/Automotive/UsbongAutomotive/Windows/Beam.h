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
 * @date created: 20201013
 * @date updated: 20201017
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
#include <stdlib.h>
#include "MyDynamicObject.h"

const int HIDDEN_STATE = 0,
          ACTIVE_STATE = 1;          

class Beam: public MyDynamicObject
{
private:	
	int currentState;

    float myXPos;
    float myYPos;
    float myZPos;
    
    float stepX;
    float stepY;
    float stepZ;
    
    float myWidthX;
    float myWidthZ;
    float myHeightY;
    
    //float boundary;

    float rotationAngle;
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
    
public:
	Beam();
	~Beam();
	//virtual ~Robot();
/*	
    virtual float getX();
	virtual float getY();
	virtual float getZ();
*/

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
    
	// draws the entire robot
	//void drawRobot(float xPos, float yPos, float zPos);
    //void drawRobotShip();
    //void drawValkyrie();
    void draw();
    
    //added by Mike, 20201013
	void drawBeam();
    
	// updates the robot data
	void update(float dt);
	
	// changes the robot's state
	void changeState(int s);
	void move(float rot, float* xyz);
	
	bool isActive(){
         if (currentState==ACTIVE_STATE)
           return true;
         else return false;
    }
    
    virtual void hitBy(MyDynamicObject* mdo);

	//added by Mike, 20201016
    virtual void destroy();
};
