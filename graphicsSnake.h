//
// Created by aidan on 4/17/2022.
//

#ifndef graphics_h
#define graphics_h

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

enum screens {homeBB};
screens getScreenSnake();
void initSnake();
void init2Snake();
void initUserSnake();

// Initialize OpenGL Graphics
void initGLSnake();

void initFoodSnake();
// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void displaySnake();
void displaySnake2();
void displayCircSnake();
// Trap and process alphanumeric keyboard events
void keyboardSnake(int key, int x, int y);

// Trap and process special keyboard events
void kbdSSnake(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursorSnake(int x, int y);
bool move2(int directions);
// Calls itself after a specified time
void timerSnake(int dummy);

// Handle mouse button pressed and released events
void mouseSnake(int button, int state, int x, int y);

#endif /* graphics_h */

