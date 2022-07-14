//
// Created by Matthew McCarthy on 5/2/22.
//

#ifndef GAME_GRAPHICSBRICKBREAKER_H
#define GAME_GRAPHICSBRICKBREAKER_H

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

enum screen {startB, inProgress, win, lose, homeB};
screen getScreenBrick();

void initPaddle();

void initBall();

void initBricks();

void initBrickBreaker();

void initGLBrickBreaker();

void displayBrickBreaker();

void kbdBrickBreaker(unsigned char key, int x, int y);

void kbdSBrickBreaker(int key, int x, int y);

void cursorBrickBreaker(int x, int y);

void mouseBrickBreaker(int button, int state, int x, int y);

void brickBreakerTimer(int dummy);

#endif //GAME_GRAPHICSBRICKBREAKER_H
