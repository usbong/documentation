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
 * @author: Michael Syson
 * @date created: 20200926
 * @date updated: 20201003
 *
 * References:
 * 1) Dev-C++ 5.11 auto-generated OpenGL example project
 *
 * 2) https://www.libsdl.org/download-2.0.php;
 * last accessed: 20200423
 *
 * 3) https://docs.microsoft.com/en-us/windows/win32/inputdev/user-input3
 * last accessed: 20200424
 *
 * 4) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL Game Programming". USA: Premier Press.
 *
 * 5) https://en.wikibooks.org/wiki/OpenGL_Programming/Basics/Structure
 * last accessed: 20200926
 *
 * 6) https://dos.gamebub.com/cpp.php
 * last accessed: 20200921
 *
 * 7) https://chortle.ccsu.edu/Bloodshed/howToGL.html
 * last accessed: 20200927
 * --> instructions to add GLUT library in Dev-C++ Editor 5.11
 *
 * 8) https://stackoverflow.com/questions/5289284/compiling-and-runnin-opengl-glut-program-in-ubuntu-10-10
 * --> last accessed: 20200928
 *
 * 9) https://askubuntu.com/questions/96087/how-to-install-opengl-glut-libraries
 * --> last accessed: 20200928
 *
 * 10) https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html
 * --> last accessed: 20200928
 * 
 * 11) https://stackoverflow.com/questions/2571402/how-to-use-glortho-in-opengl/36046924#36046924;
 * --> last accessed: 20200928
 * --> answers by: Mikepote, 20100408T1912
 * --> answers by: Santilli, Ciro, 20160316T2106
 *
 * 
 * Notes:
 * 1) We can use this software tool to extract the compressed (zipped) folder.
 *   https://www.7-zip.org/download.html; last accessed: 20200423
 *
 * 2) OpenGL (Open Graphics Library) Utility Toolkit Library
 *
 * 3) Linux Machine
 * 3.1) Compile Command
 *   g++ main.cpp -o mainOutput -lGL -lGLU -lglut
 *
 * 3.2) Execute Command
 *   ./mainOutput
 *
 * 3.3) Install OpenGL Libraries
 *   sudo apt-get install mesa-utils
 *
 * 3.4) Install GLUT Library
 *   sudo apt-get install freeglut3-dev
 *
 * 4) macOS Machine
 * 4.1) Install OpenGL Libraries
 *  brew install mesa
 *  Reference: https://formulae.brew.sh/formula/mesa; last accessed: 20201003
 *
 * 4.2) Install GLUT Library
 *  brew install freeglut
 *  Reference: https://formulae.brew.sh/formula/freeglut; last accessed: 20201003
 *
 */


/**************************
 * Includes
 *
 **************************/

//#include <windows.h> //removed by Mike, 20200928 due to Linux Machine

//edited by Mike, 20201003
//#include <GL/gl.h>
//#include <GL/glut.h> //added by Mike, 20200927
//#include <GL/glu.h> //added by Mike, 20200926

//added by Mike, 20201003
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//added by Mike, 20200930
#include "OpenGLCanvas.h"

//added by Mike, 20201002
#include <iostream>

/**************************
 * Function Declarations
 *
 **************************/
/*
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
*/

//added by Mike, 20201002
#define VK_UP 101
#define VK_DOWN 103
#define VK_LEFT 100
#define VK_RIGHT 102

//note: "static" in C/C++ = "final" in java
static int myWindowWidth=640; //320
static int myWindowHeight=640; //320

//added by Mike, 20201001
OpenGLCanvas *myOpenGLCanvas = NULL;

//added by Mike, 20201001
enum Keys
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_SPACE,
	KEY_ENTER
};

//added by Mike, 20201001
bool pause;

//Reference: https://www3.ntu.edu.sg/home/ehchua/programming/opengl/HowTo_OpenGL_C.html;
//last accessed: 20200928
void displayExample() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();
 
   glFlush();  // Render now
}

//added by Mike, 20200928; edited by Mike, 20200930
void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
 
   //set TOP-LEFT origin/anchor/reference point; quadrant 4, y-axis inverted; x and y positive
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 //TOP-Left origin
	 glOrtho(0.0f, //left
        	1.0f, //right
        	1.0f, //bottom
        	0.0f, //top
        	0.0f, //zNear; minimum
        	1.0f //zFar; maxinum
      	);
	
	 //draw grid 
 	 //TO-DO: -update: iRowCountMax
 	 int iRowCountMax=10;
 	 //TO-DO: -update: iColumnCountMax
 	 int iColumnCountMax=10;

   // Draw a Green Line top-left origin; Quadrant 4, y-axis inverted; x and y positive
   //rows   
 	 for (int iRowCount=0; iRowCount<iRowCountMax; iRowCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.0f, 0.1f*iRowCount);    // x, y
      		//TO-DO: -add: auto-compute myWindowWidth
      		glVertex2f(1.0f, 0.1f*iRowCount);
   		glEnd();   		   	  
	 }

   //columns
 	 for (int iColumnCount=0; iColumnCount<iColumnCountMax; iColumnCount++) {
   		// Draw a Green Line top-left origin
   		glBegin(GL_LINES);
      		glColor3f(0.0f, 1.0f, 0.0f); // Green
      		glVertex2f(0.1f*iColumnCount, 0.0f);    // x, y
      		//TO-DO: -add: auto-compute myWindowHeight
      		glVertex2f(0.1f*iColumnCount, 1.0f);
   		glEnd();   		   	  
	 }
   
   glFlush();  // Render now
}

//added by Mike, 20200930
void displayOpenGLCanvas() {
	 //removed by Mike, 20200930	 
	 //Linux Machine
/*    myOpenGLCanvas = new OpenGLCanvas;
    myOpenGLCanvas->init();
*/

	//added by Mike, 20201001
    //init stuff for delay
    int skip=0, currSysTime=0,
        timeElapsed,
        idealFrameTime=60;//33;
    pause=false;//0;
	 
		if (!pause) {
					//removed by Mike, 20201002					
          //currSysTime=GetTickCount(); //Linux Machine

          /* OpenGL animation code goes here */
          myOpenGLCanvas->update();
/*				//removed by Mike, 20201002, Linux Machine
          if (skip > 0)
              skip = skip-1;
          else {
*/          
                //do rendering here 
                myOpenGLCanvas->render();
                //removed by Mike, 20201002
                //SwapBuffers (hDC); //Windows Machine
   							glFlush();  // Render now //Linux Machine

/*							//removed by Mike, 20201002, Linux Machine                
                timeElapsed=GetTickCount()-currSysTime;
                if (timeElapsed>idealFrameTime)
                  skip = (timeElapsed/idealFrameTime) - 1;
                else 
                  Sleep(idealFrameTime - timeElapsed);
          }
*/                  
		  //added by Mike, 20201002
//			glutPostRedisplay();
			
			//reference: https://stackoverflow.com/questions/35563360/looping-in-opengl-with-gluttimerfunc;
			//answer by: spookyPuppy, 20160223T0445
			//edited by: datenwolf, 20160223T0631			
			//note: void glutTimerFunc(unsigned int numMilliseconds, functionCallback, value);
			//glutTimerFunc(1000 / SCREEN_FPS, Loop, 0);
//			glutTimerFunc(1000, NULL, 0);

		}	 
}

//added by Mike, 20200930
void update(int i) {
	 //removed by Mike, 20200930	 
	 //Linux Machine
/*    myOpenGLCanvas = new OpenGLCanvas;
    myOpenGLCanvas->init();
*/

	//added by Mike, 20201001
    //init stuff for delay
    int skip=0, currSysTime=0,
        timeElapsed,
        idealFrameTime=60;//33;
    pause=false;//0;
	 
		if (!pause) {
					//removed by Mike, 20201002					
          //currSysTime=GetTickCount(); //Linux Machine

          /* OpenGL animation code goes here */
          myOpenGLCanvas->update();
/*				//removed by Mike, 20201002, Linux Machine
          if (skip > 0)
              skip = skip-1;
          else {
*/          

/*							//removed by Mike, 20201002, Linux Machine                
                timeElapsed=GetTickCount()-currSysTime;
                if (timeElapsed>idealFrameTime)
                  skip = (timeElapsed/idealFrameTime) - 1;
                else 
                  Sleep(idealFrameTime - timeElapsed);
          }
*/                  
		  //added by Mike, 20201002
			glutPostRedisplay();
			
			//reference: https://stackoverflow.com/questions/35563360/looping-in-opengl-with-gluttimerfunc;
			//answer by: spookyPuppy, 20160223T0445
			//edited by: datenwolf, 20160223T0631			
			//note: void glutTimerFunc(unsigned int numMilliseconds, functionCallback, value);
			//glutTimerFunc(1000 / SCREEN_FPS, Loop, 0);
			glutTimerFunc(50, update, 0);
			
			//TO-DO: -add: image buffer to reduce flickering due to repainting canvas
		}	 
}



//note: special functions, e.g. character keys
//added by Mike, 20201002
void keyDown (unsigned char key, int x, int y)
{
//    std::cout << "keydown " << key << "\n";
}
//added by Mike, 20201002
void keyUp (unsigned char key, int x, int y)
{
//    std::cout << "keyup " << key << "\n";
}

//note: special functions, e.g. shift, control, arrow keys
//UP: 101
//DOWN: 103
//LEFT: 100
//RIGHT: 102    
//added by Mike, 20201002
void specialKeyDown (int specialKey, int x, int y)
{
//    std::cout << "keydown " << specialKey << "\n";  
  
    switch (specialKey)
    {
/*				//TO-DO: -add: this        
	        case VK_ESCAPE:
	            PostQuitMessage(0);
	            return 0;
*/	            
	        //added by Mike, 20201001
   	       case VK_LEFT:
		        		myOpenGLCanvas->keyDown(KEY_LEFT);
                return;
   	       case VK_RIGHT:
		        		myOpenGLCanvas->keyDown(KEY_RIGHT);
                return;
   	       case VK_UP:
		        		myOpenGLCanvas->keyDown(KEY_UP);
                return;
   	       case VK_DOWN:
		        		myOpenGLCanvas->keyDown(KEY_DOWN);
                return; 
/*				 //removed by Mike, 20201002                    
   	       case VK_SPACE:
                myOpenGLCanvas->keyDown(KEY_SPACE);
                return;
*/                
			//removed by Mike, 20201001 
/*			               
   	       case 13: //ENTER
                myOpenGLCanvas->keyDown(KEY_ENTER);
                return;     
   	       case 80: //P
   	            if (myOpenGLCanvas->currentState!=TITLE_SCREEN) {
			        if (pause==0) //false
			          pause=1; //make it true
                    else pause=0;
                }
                return;     	        
*/                
        }
        return;

}
//added by Mike, 20201002
void specialKeyUp (int specialKey, int x, int y)
{
//    std::cout << "keyup " << specialKey << "\n";
    
		switch (specialKey)
    {
   	       case VK_LEFT:
		        		myOpenGLCanvas->keyUp(KEY_LEFT);
                return;
   	       case VK_RIGHT:
		        		myOpenGLCanvas->keyUp(KEY_RIGHT);
                return;
   	       case VK_UP:
		        		myOpenGLCanvas->keyUp(KEY_UP);
                return;
   	       case VK_DOWN:
		        		myOpenGLCanvas->keyUp(KEY_DOWN);
                return;
/*         //removed by Mike, 20201002
   	       case VK_SPACE:
                myOpenGLCanvas->keyUp(KEY_SPACE);
                return;
*/                
        }
        return;    
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   //edited by Mike, 20200930
   glutCreateWindow("Usbong OpenGL Halimbawa"); // Create a window with the given title
   glutInitWindowSize(myWindowWidth, myWindowHeight);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	 
	  //added by Mike, 20201002
	  //Linux Machine
	  //note: to receive key presses
    myOpenGLCanvas = new OpenGLCanvas;
    myOpenGLCanvas->init();

	 	//edited by Mike, 20200930
   	//glutDisplayFunc(display); // Register display callback handler for window re-paint	

   	//edited by Mike, 20201002
//	 	glutDisplayFunc(displayOpenGLCanvas); // Register display callback handler for window re-paint
	 	glutDisplayFunc(displayOpenGLCanvas); // Register display callback handler for window re-paint
	 	//displayOpenGLCanvas(); //output of this = glutDisplayFunc(displayOpenGLCanvas);
	 		
	 	update(0);
	 		
	 	//added by Mike, 20201002
	 	glutKeyboardFunc(keyDown);
   	glutKeyboardUpFunc(keyUp);
	 	glutSpecialFunc(specialKeyDown);
	 	glutSpecialUpFunc(specialKeyUp);
    		
   	glutMainLoop();           // Enter the infinitely event-processing loop
   	

   return 0;
}


/**************************
 * WinMain
 *
 **************************/
/*
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    // register window class
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    // create main window    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
	//added by Mike, 20200926
    int myWindowWidth=640;
    int myWindowHeight=640;


    hWnd = CreateWindow (
      "GLSample", "Usbong OpenGL Halimbawa", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, myWindowWidth, myWindowHeight,
      NULL, NULL, hInstance, NULL);

    // enable OpenGL for the window
    EnableOpenGL (hWnd, &hDC, &hRC);

    // program main loop
    while (!bQuit)
    {
        // check for messages
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // handle or dispatch messages
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            // OpenGL animation code goes here

            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);


			//added by Mike, 20200926
		    // setup OpenGL initial state
		    glEnable(GL_CULL_FACE);   // cull back faces
		    glEnable(GL_DEPTH_TEST);  // enable Z-buffer
		    //glEnable(GL_LIGHTING);    // enable lighting
		    glEnable(GL_NORMALIZE);   // renormalize all vertex normals
		
		    // enable Gouraud shading
		    // (this is default--code appears here only for emphasis)
		    glShadeModel(GL_SMOOTH);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
//    		glViewport(0-myWindowWidth/2, 0-myWindowHeight/2, myWindowWidth, myWindowHeight);		// reset the viewport to new dimensions

			//TO-DO: -update: this
			//Reference: https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html;
			//last accessed: 20200927
			// Set to 2D orthographic projection with the specified clipping area
			glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
			glLoadIdentity();                 // Reset Projection matrix
			gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set clipping area's left, right, bottom, top

    		glViewport(0, 0, myWindowWidth, myWindowHeight);		// reset the viewport to new dimensions

			// Draws two horizontal lines
            glPushMatrix ();			
			glBegin(GL_LINES);
              glColor3f (0.0f, 1.0f, 0.0f);
              //TO-DO: -add: grid
              //note: one (1) line, two (2) vertices
			  //X,Y coordinate position from center as reference point
			  //TO-DO: -update: this
			  //X,Y coordinate position from top-left as reference point
//			  glVertex2f(0.0f, 0.9f);
//			  glVertex2f(0.9f, 0.9f); 

			  glVertex2f(0.0f, 0.5f);
			  glVertex2f(0.5f, 0.5f); 

			glEnd();            
            glPopMatrix ();
            SwapBuffers (hDC);    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
            
            //TO-DO: -add: read input file with vertices
            //refer: https://all-things-andy-gavin.com/2020/02/27/war-stories-crash-bandicoot/
            //last accessed: 20200926
        }
    }

    // shutdown OpenGL
    DisableOpenGL (hWnd, hDC, hRC);

    // destroy the window explicitly
    DestroyWindow (hWnd);

    return msg.wParam;
}
*/

/********************
 * Window Procedure
 *
 ********************/
/*
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}
*/

/*******************
 * Enable OpenGL
 *
 *******************/
/*
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
    *hDC = GetDC (hWnd);

    // set the pixel format for the DC 
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    // create and enable the render context (RC) 
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}
*/

/******************
 * Disable OpenGL
 *
 ******************/
/*
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
*/
