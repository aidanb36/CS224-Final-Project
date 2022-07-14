//
// Created by aidan on 5/2/2022.
//

#ifndef GAME_GAPHICSHOME_H
#define GAME_GAPHICSHOME_H

#include <string>
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

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void initHome();

// Initialize OpenGL Graphics
void initGLHome();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void displayHome();

// Trap and process alphanumeric keyboard events
void kbdHome(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursorHome(int x, int y);

// Calls itself after a specified time
//void timer(int dummy);

// Handle mouse button pressed and released events
void mouseHome(int button, int state, int x, int y);
std::string mouseHome2(int button, int state, int x, int y);

#endif //GAME_GAPHICSHOME_H
