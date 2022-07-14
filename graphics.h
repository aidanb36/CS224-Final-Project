//
// Created by Heshi Muntiu on 4/28/22.
//

#ifndef GAME_GRAPHICS_H
#define GAME_GRAPHICS_H


#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//enum arcade {home,flappy,snake,doodle};
//arcade arcadeGame;

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet

void init();

// Initialize OpenGL Graphics
void InitGL();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void display();

// Trap and process alphanumeric keyboard events
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

void kbdSUp(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursor(int x, int y);

// Calls itself after a specified time
void timer(int dummy);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);


#endif //GAME_GRAPHICS_H
