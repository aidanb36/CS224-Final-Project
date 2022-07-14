//
// Created by Xantia Kansil on 4/28/22.
//

#ifndef GAME_GRAPHICSFLAPPYBIRD_H
#define GAME_GRAPHICSFLAPPYBIRD_H


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


enum state {start,game,hit,over,flappyLeaderboard,goHomeScreen};
state getStateFlappy();

void initPlayerFlappy();
void initFlappy();

void initPipesFlappy();

// Initialize OpenGL Graphics
void InitGLFlappy();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void displayFlappy();

// Trap and process alphanumeric keyboard events
void kbdFlappy(unsigned char key, int x, int y);

// Handle "mouse cursor moved" events
void cursorFlappy(int x, int y);

// Calls itself after a specified time
void playerTimerFlappy(int dummy);
void pipeTimerFlappy(int dummy);

// Handle mouse button pressed and released events
void mouseFlappy(int button, int state, int x, int y);




#endif //GAME_GRAPHICSFLAPPYBIRD_H
