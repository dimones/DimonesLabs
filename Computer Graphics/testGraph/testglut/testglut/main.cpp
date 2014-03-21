//
//  main.cpp
//  testglut
//
//  Created by Дмитрий Богомолов on 17.03.14.
//  Copyright (c) 2014 Dimones. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenAl/al.h>
#include <OpenAL/alc.h>
#include <GLUT/glut.h>

using namespace std;
const int WIDTH = 1280;
const int HEIGHT = 720;
const char* TITLE = "Line Methods";

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glutSwapBuffers();
    
}


int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow(TITLE);
    glutDisplayFunc(display);
    glutMainLoop();
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


