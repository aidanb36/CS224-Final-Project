//
// Created by Xantia Kansil on 5/3/22.
//

#ifndef GAME_GRAPHICSDOODLE_H
#define GAME_GRAPHICSDOODLE_H




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

enum gameState {startD,gameD,endD,goHomeScreenD};
gameState getStateDoodle();

void initPlayerDoodle();
void initDoodle();
void initGLDoodle();

void initTilesDoodle();

// Initialize OpenGL Graphics
void InitGLDoodle();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void displayDoodle();

// Trap and process alphanumeric keyboard events
void kbdDoodle(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdSDoodle(int key, int x, int y);


void kbdSUpDoodle(int key, int x, int y);

// Handle "mouse cursor moved" events
void cursorDoodle(int x, int y);

// Calls itself after a specified time
void playerTimerDoodle(int dummy);
void tileTimerDoodle(int dummy);
void tileTimerXDoodle(int dummy);
void playerTimerXDoodle(int dummy);



// Handle mouse button pressed and released events
void mouseDoodle(int button, int state, int x, int y);


#endif //GAME_GRAPHICSDOODLE_H
