//
// Created by Matthew McCarthy on 5/2/22.
//

#include "graphics.h"
#include "graphicsBrickBreaker.h"
#include "Player.h"
#include "Button.h"
#include "rect.h"
#include "circle.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string>
using namespace std;

GLdouble widthB, heightB;
int wdB;

color brickRed(201/255.0, 20/255.0, 20/255.0);
color blue(0, 0, 1);
color hoverColorB(.2,.2,1);
color pressColorB(0,0,1);
color releaseColorB(0.3,0.4,1);

Button goHomeBrick(50, 50, 100, 40, "Go Home", .5, .5, 1);
Button goStartBrick(250, 400, 100, 40, "Replay", .5, .5, 1);

Rect paddle;
Circle ball;
Rect ball2;

vector<Rect> bricks;

int xVelB;
int yVelB;

dimensions brickSize (20,22);
dimensions ballSize(10,10);

screen scr;



screen getScreenBrick(){
    return scr;
}

void initPaddle(){

    paddle.setCenter(250, 480);
    paddle.setSize(50, 10);
    paddle.setFillColor(blue);

}


void initBall(){
    ball.setCenter(250,250);
    ball.setRadius(5);
    xVelB = 2;
    yVelB = 6;
    ball2.setSize(ballSize);

}

void initBricks(){


    for (int i = 22; i < widthB; i += 22) {
        for (int j = 25; j < heightB/6; j += 25) {
            bricks.push_back(
                    Rect(1.0, 0.0, 0.0, 1.0, i, j, brickSize));
        }
    }

}

void initBrickBreaker() {
    widthB = 500;
    heightB = 500;
    srand(time(0));
    initPaddle();
    initBall();
    initBricks();
    scr = startB;
}

/* Initialize OpenGL Graphics */
void initGLBrickBreaker() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}
void displayBrickBreaker() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, widthB, heightB);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, widthB, heightB, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */

    //Start Screen
    if (scr == startB){
        //Prompt to press s key
        string label = "Welcome to Brick Breaker! Press the S key to begin.";
        glColor3f(201/255.0, 20/255.0, 20/255.0);
        point2D center = {250, 250};
        glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    //Game in progress screen
    if (scr == inProgress){
        for (Rect &brick : bricks) {
            brick.draw();
        }
        paddle.draw();
        ball.draw();

        ball2.setCenter(ball.getCenterX(), ball.getCenterY());

        ball.move(ball.getXVelocity(), ball.getYVelocity());

        if(ball.getCenterY() < paddle.getBottomY() && ball.getCenterY() > paddle.getTopY() && ball.getCenterX() < paddle.getRightX() && ball.getCenterX() > paddle.getLeftX()){
            ball.bounceY();
        }

        if(ball.getCenterX() > widthB || ball.getCenterX() < 0){
            ball.bounceX();
        }

        if(ball.getCenterY() < 0){
            ball.bounceY();
        }

        for(int i = 0; i < bricks.size(); i++){
           if(bricks[i].isOverlapping(ball2)){
               if(ball.getCenterY() > (bricks[i].getBottomY() - 5)) {
                   ball.bounceY();
                   bricks.erase(bricks.begin() + i);
               }
               else if (ball.getCenterY() < (bricks[i].getTopY() + 5)) {
                   ball.bounceY();
                   bricks.erase(bricks.begin() + i);
               }
               else if (ball.getCenterX() < (bricks[i].getLeftX() + 5)) {
                   ball.bounceX();
                   bricks.erase(bricks.begin() + i);
               }
               else if (ball.getCenterX() > (bricks[i].getRightX() - 5)) {
                   ball.bounceX();
                   bricks.erase(bricks.begin() + i);
               }
           }
        }

        if(ball.getCenterY() > 500){
            scr = lose;
        }

        if(bricks.size() == 0){
            scr = win;
        }

    }

    //Game ended with win
    if (scr == win){
        string label = "You have beaten Brick Breaker!";
        glColor3f(201/255.0, 20/255.0, 20/255.0);
        point2D center = {250, 400};
        glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        goHomeBrick.draw();
    }
    //Game ended with loss
    if (scr == lose){
        string label = "Better luck next time!";
        glColor3f(201/255.0, 20/255.0, 20/255.0);
        point2D center = {250, 250};
        glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        goHomeBrick.draw();
    }

    //glFlush();  // Render now
}

void kbdBrickBreaker(unsigned char key, int x, int y) {
     //s key
    if (key == 83 || key == 115) {
        scr = inProgress;
   }

    if (key == 32){
        ball.setVelocity(xVelB, yVelB);
    }

    // escape
    if (key == 27) {
        glutDestroyWindow(wdB);
        exit(0);
    }

    //glutPostRedisplay();
}

void kbdSBrickBreaker(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            paddle.move(-20,0);
            break;
        case GLUT_KEY_RIGHT:
            paddle.move(20,0);
            break;
        case GLUT_KEY_UP:
            break;
    }

    //glutPostRedisplay();
}

void cursorBrickBreaker(int x, int y) {

    paddle.setCenterX(x);

    //goHome button
    if (goHomeBrick.isOverlapping(x,y)){
        goHomeBrick.hover(hoverColorB);
    }
    else{
        goHomeBrick.release(releaseColorB);
    }

    //goStart button
    if (goStartBrick.isOverlapping(x,y)){
        goStartBrick.hover(hoverColorB);
    }
    else{
        goStartBrick.release(releaseColorB);
    }

    //glutPostRedisplay();
}

void mouseBrickBreaker(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && goHomeBrick.isOverlapping(x, y)) {
        goHomeBrick.press(pressColorB);
    } else {
        goHomeBrick.release(releaseColorB);
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && goHomeBrick.isOverlapping(x, y)) {
        goHomeBrick.hover(hoverColorB);
        scr = homeB;
        goHomeBrick.release(releaseColorB);
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && goStartBrick.isOverlapping(x, y)) {
        goStartBrick.press(pressColorB);
    } else {
        goStartBrick.release(releaseColorB);
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && goStartBrick.isOverlapping(x, y)) {
        goStartBrick.hover(hoverColorB);
        scr = startB;
        goStartBrick.release(releaseColorB);
    }
    //glutPostRedisplay();
}

void brickBreakerTimer(int dummy) {

    //glutPostRedisplay();
    //glutTimerFunc(30, brickBreakerTimer, dummy);
}




#include "graphicsBrickBreaker.h"
