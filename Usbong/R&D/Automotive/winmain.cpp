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
 * @date created: 2006
 * @date updated: 20200424
 *
 * References:
 * 1) https://www.libsdl.org/download-2.0.php;
 * last accessed: 20200423
 *
 * 2) https://docs.microsoft.com/en-us/windows/win32/inputdev/user-input3
 * last accessed: 20200424
 *
 * 3) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL Game Programming". USA: Premier Press.
 *
 * Note:
 * 1) We can use this software tool to extract the compressed (zipped) folder.
 *   https://www.7-zip.org/download.html; last accessed: 20200423
 *
 */

/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>

//added by Mike, 20200424
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN

//added by Mike, Dec. 15, 2006
//#include "OpenGLCanvas.h"

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

//added by Mike, Dec. 15, 2006
//OpenGLCanvas *myOpenGLCanvas = NULL;

enum Keys
{
	KEY_UP = 0,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT
};

/**************************
 * WinMain
 *
 **************************/

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

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "UsbongRobot";
    RegisterClass (&wc);

    
	/* create main window */
    hWnd = CreateWindow (
      "UsbongRobot", "UsbongRobot", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
//      0, 0, 512, 512, //256
      0, 0, 1024, 1024, //256
      NULL, NULL, hInstance, NULL);


	//added by Mike, 20200424
	//register input device, e.g. gamepad
	RAWINPUTDEVICE Rid[1];
	        
	Rid[0].usUsagePage = 0x01; 
	Rid[0].usUsage = 0x05; 
	Rid[0].dwFlags = 0;                 // adds game pad
	Rid[0].hwndTarget = 0; //hWnd;

	if (RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])) == FALSE) {
	    //registration failed. Call GetLastError for the cause of the error.		
		MessageBox(NULL, "Registration Failed.", "Message Box", NULL);
	}

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    //added by Mike, Dec. 15, 2006
//    myOpenGLCanvas = new OpenGLCanvas;
//    myOpenGLCanvas->init();
   
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
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
            /* OpenGL animation code goes here */
//            myOpenGLCanvas->update();
//            myOpenGLCanvas->render();
/*
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            glPushMatrix ();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.87f, -0.5f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
            glEnd ();
            glPopMatrix ();
*/
            SwapBuffers (hDC);

            theta += 1.0f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    //added by Mike, Dec. 15, 2006
    int width, height;

    switch (message)
    {
        case WM_CREATE:
            return 0;
        case WM_CLOSE:
            PostQuitMessage (0);
            return 0;
    
        case WM_DESTROY:
            return 0;
    
        //added by Mike, Dec. 15, 2006
    	case WM_SIZE:
            // retrieve width and height
    		width = LOWORD(lParam);
    		height = HIWORD(lParam);		
    
//    		//myOpenGLCanvas->setupProjection(width, height);
    		return 0;

		//added by Mike, 20200424; edited by Mike, 20200428
		case WM_INPUT:
	 		{
		        PRAWINPUT pRawInput;
		        PRAWINPUT pRawHeaderInput;

		        UINT      bufferSize;
		        HANDLE    hHeap;
		
				UINT iResult;

		        GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, 
				&bufferSize, sizeof(RAWINPUTHEADER));
		
		        hHeap     = GetProcessHeap();
		        pRawInput = (PRAWINPUT)HeapAlloc(hHeap, 0, bufferSize);
		        if(!pRawInput) {
		            return 0;
				}

		        iResult = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
				pRawInput, &bufferSize, sizeof(RAWINPUTHEADER));
/*				
				char sBufferSize[5];
				MessageBox(NULL, itoa(bufferSize,sBufferSize,10),"Message Box", NULL);
*/

//				MessageBox(NULL, (char*)pRawInput,"Message Box", NULL);
		

		        GetRawInputData((HRAWINPUT)lParam, RID_HEADER, NULL, 
				&bufferSize, sizeof(RAWINPUTHEADER));
		
		        hHeap     = GetProcessHeap();
		        pRawHeaderInput = (PRAWINPUT)HeapAlloc(hHeap, 0, bufferSize);
		        if(!pRawInput) {
		            return 0;
				}
		
		        iResult = GetRawInputData((HRAWINPUT)lParam, RID_HEADER, 
				pRawHeaderInput, &bufferSize, sizeof(RAWINPUTHEADER));



/*				if (iResult==0) { //success
				}
*/				
/*
				char snum[5];
				MessageBox(NULL, itoa(iResult, snum, 10), "Message Box", NULL);
*/
				//https://docs.microsoft.com/en-gb/windows/win32/api/winuser/nf-winuser-getrawinputdata;
				//last accessed: 20200426
				
				//if iResult == 0, pData is null and function is successful
				if (iResult==-1) { //error
				  return -1;
				}
				//else, return value is number of bytes copied to pData

				
		 //       ParseRawInput(pRawInput);


			INT rawDataSize = pRawInput->data.hid.dwCount*pRawInput->data.hid.dwSizeHid;
/*
//            BYTE * returnval = new BYTE[rawDataSize];
            	char * returnval = new char[rawDataSize];
				returnval = pRawInput->data.hid.bRawData;
*/

//			char snum[5];
//			MessageBox(NULL, itoa(rawDataSize, snum, 10),"Message Box", NULL);

//			char snum[5];
//			MessageBox(NULL, itoa(pRawInput->data.hid.dwCount, snum, 10),"Message Box", NULL);


/* //output: random number
			char snum[5];
			MessageBox(NULL, ltoa(lParam, snum, 10),"Message Box", NULL);
*/

/* //output: 0
			char snum[5];
			MessageBox(NULL, itoa(wParam, snum, 10), "Message Box", NULL);
*/

/*
			char snum[5];
//			MessageBox(NULL, pRawInput->data.hid.bRawData,"Message Box", NULL);
			memcpy(snum, pRawInput->data.hid.bRawData, 5);
			MessageBox(NULL, snum, "Message Box", NULL);
*/
				

	//      char* ss = (char*) s; // put breakpoint here or watch the variable
	      char* ss = (char*) pRawInput->data.hid.bRawData; // put breakpoint here or watch the variable

	      char* ssHeader = (char*) pRawHeaderInput->data.hid.bRawData; // put breakpoint here or watch the variable

/*	
			//note: output: 0
				char snum[5];
				MessageBox(NULL, itoa(strlen(ss),snum,10),"Message Box", NULL);
*/	

		  //Note:
		  //in gamepad, i.e. SideWinder Game Pad USB (Microsoft - Malaysia) 
		  // if size 2, single dot, double dot, Z, and A buttons use equal values
		  //if we increase the size, the buttons with equal values vary

		  //+verified: to receive as output unique values
		  //by using in addition the raw input's header value, we can eliminate the buttons with equal values
		  //This is except for double dot and A buttons whose output value remains equal

		  char sOutput[2];
	
		  //Reference:
		  //https://stackoverflow.com/questions/7592930/how-to-view-content-of-variable-of-type-lpvoid;
		  //last accessed: 20200428
		  //answer by: user350954 on 20110929T0558; edited on 20110929T0625
	
		  int iCount = 0;
	//      for(char* r = ss; *r != '\0'; r += (strlen(r)+1)) { // iterate the string
	      for(char* r = ss; iCount < 2; r += (strlen(r)+1)) { // iterate the string
	
	//			MessageBox(NULL, r,"Message Box", NULL);
	
				strcat(sOutput, r);
	
	//          printf("%s \n", r);
				iCount++;
	       }   
			

			MessageBox(NULL, sOutput,"Message Box", NULL);

		//--------------------------
		
		  char sHeaderOutput[10];

		  iCount = 0;
	//      for(char* r = ss; *r != '\0'; r += (strlen(r)+1)) { // iterate the string
	      for(char* r = ss; iCount < 10; r += (strlen(r)+1)) { // iterate the string
	
	//			MessageBox(NULL, r,"Message Box", NULL);
	
				strcat(sHeaderOutput, r);
	
	//          printf("%s \n", r);
				iCount++;
	       }   

			MessageBox(NULL, sHeaderOutput,"Message Box", NULL);

		    HeapFree(hHeap, 0, pRawInput);
		    HeapFree(hHeap, 0, pRawHeaderInput);

				return 0;		
		    }		    
	    case WM_KEYDOWN:        	
			//added by Mike, 20200424
//			MessageBox(NULL, "PRESSED: " + (TCHAR)wParam, "Message Box", NULL);

            switch (wParam)
            {
                   case VK_ESCAPE:
                        PostQuitMessage(0);
                        return 0;
           	       case VK_LEFT:
						//added by Mike, 20200424
//						MessageBox(NULL, "PRESSED LEFT KEY!", "Message Box", NULL);
//				        myOpenGLCanvas->keyDown(KEY_LEFT);
                        return 0;
           	       case VK_RIGHT:
//				        myOpenGLCanvas->keyDown(KEY_RIGHT);
                        return 0;
           	       case VK_UP:
//				        myOpenGLCanvas->keyDown(KEY_UP);
                        return 0;
           	       case VK_DOWN:
//				        myOpenGLCanvas->keyDown(KEY_DOWN);
                        return 0;                        
            }
            return 0;
       	case WM_KEYUP:
            switch (wParam)
            {
           	       case VK_LEFT:
//				        myOpenGLCanvas->keyUp(KEY_LEFT);
                        return 0;
           	       case VK_RIGHT:
//				        myOpenGLCanvas->keyUp(KEY_RIGHT);
                        return 0;
           	       case VK_UP:
//				        myOpenGLCanvas->keyUp(KEY_UP);
                        return 0;
           	       case VK_DOWN:
//				        myOpenGLCanvas->keyUp(KEY_DOWN);
                        return 0;                        
            }
        default:        	
            return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
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

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
