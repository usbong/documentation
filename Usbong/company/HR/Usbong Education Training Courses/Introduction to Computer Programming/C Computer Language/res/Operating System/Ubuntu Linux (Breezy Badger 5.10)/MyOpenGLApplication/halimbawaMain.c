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
 * @author: SYSON, MICHAEL
 * @date created: 20200712
 * @last updated: 20200712
 *
 * @Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Basics/Structure;
 * last accessed: 20200712
 */

#ifndef WIN32
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

//include <windows.h>
#endif

#include <stdio.h>
//#include "/usr/include/stdio.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

void setup() {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0f, 0.0f, 0.0f);
  glRectf(-0.75f, 0.75f, 0.75f, -0.75f);
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
//  printf("Kumusta!\n");


  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(800,600);
  glutCreateWindow("Kumusta!");

  setup();
  glutDisplayFunc(display);
  
  glutMainLoop();
  
  return 0;
}
