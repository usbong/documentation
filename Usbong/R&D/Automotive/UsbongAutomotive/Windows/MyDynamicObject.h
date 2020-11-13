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
 * @date updated: 20201113
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

//TO-DO: -update: this

#ifndef MYDYNAMICOBJECT_H
#define MYDYNAMICOBJECT_H

#include <Math.h>
#include <stdlib.h>

class MyDynamicObject
{
private:        
	//TO-DO: -add: collisionBoxes
    float **collisionSpheres;
    int csSize; //to allow multiple spheres
    int maxSize;
    int i;
    bool isCollidable;

public:
    float myXPos;
    float myYPos;
    float myZPos;
    
    float myWidth;
    float myHeight;

	//edited by Mike, 20201113
//    MyDynamicObject(float xPos = 0.0f, float yPos = 0.0f, float zPos= 300.0f ): myXPos(xPos), myYPos(yPos), myZPos(zPos) 
    MyDynamicObject(float xPos = 0.0f, float yPos = 0.0f, float zPos= 0.0f ): myXPos(xPos), myYPos(yPos), myZPos(zPos) 
    //{myXPos=0.0f; myYPos=0.0f; myZPos=300.0f;}
    {}
    virtual void hitBy(MyDynamicObject* mdo);
        
    //collision stuff
    bool checkIsCollidable();
    void setCollidable(bool c);

    void initializeCollisionSpheres(int ms);
    
    void addSphere(float dx, float dy, float dz, float r);
	
	float** getCollisionSpheres();

    int getNumSpheres();
    
    virtual float getX()=0;
    virtual float getY()=0;
    virtual float getZ()=0;
    
    virtual float getWidth()=0;
    virtual float getHeight()=0;
    
    float getDistance(float x1, float y1, float z1, float x2, float y2, float z2);
    
    bool checkCollision(MyDynamicObject* mdo1, MyDynamicObject* mdo2);
    void collideWith(MyDynamicObject* mdo);
        
    bool isIntersectingRect(MyDynamicObject* mdo1, MyDynamicObject* mdo2);
    
    //added by Mike, 20201016
    virtual void destroy();
};

#endif
