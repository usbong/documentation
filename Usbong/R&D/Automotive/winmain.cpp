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
 * @date updated: 20200423
 *
 * Reference:
 * 1) https://www.libsdl.org/download-2.0.php;
 * last accessed: 20200423
 *
 * Note:
 * 1) We can use this software tool to extract the compressed (zipped) folder.
 *   https://www.7-zip.org/download.html; last accessed: 20200423
 */

/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>

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
    
        case WM_KEYDOWN:
            switch (wParam)
            {
                   case VK_ESCAPE:
                        PostQuitMessage(0);
                        return 0;
           	       case VK_LEFT:
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
