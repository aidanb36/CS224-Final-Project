//
// Created by Heshi Muntiu on 5/1/22.
//



#include "graphics.h"
#include "DoodlePlayer.h"
#include "Tile.h"
#include <cmath>
#include <iostream>
#include <cmath>
using namespace std;


DoodlePlayer::DoodlePlayer(int x, int y) {
    centerX = x;
    centerY = y;
    red = 1;
    green = 0;
    blue = 0;
}

void DoodlePlayer::moveX(int x) {
    centerX += x;
}

void DoodlePlayer::moveY(int y) {
    centerY += y;
}


void DoodlePlayer::setX(int x){
    centerX = x;
}

void DoodlePlayer::setY(int y){
    centerY = y;
}

int DoodlePlayer::getCenterY() {
    return centerY;
}

int DoodlePlayer::getCenterX() {
    return centerX;
}

bool DoodlePlayer::bounce(Tile t, int vel){
    if((centerX - 10 < t.getRightX()) && (centerX > t.getCenterX()) || (centerX + 10 > t.getLeftX()) && (centerX < t.getCenterX()) ){
        if (centerY + 10 > t.getTopY() - 10 && centerY < t.getBottomY() + 10 ){
            if (vel > 0){
                return true;
            }
        }
    }
    return false;
}

void DoodlePlayer::draw(){
    //draw circle
    glColor3f(red,green,blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(centerX, centerY);
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(centerX + (10 * cos(i)),
                   centerY - 10 + (10 * sin(i)));
    }
    glEnd();
    //draw rectangle
    glBegin(GL_QUADS);
    glVertex2i(centerX + 10, centerY - 10);
    glVertex2i(centerX + 10, centerY + 10);
    glVertex2i(centerX - 10, centerY + 10);
    glVertex2i(centerX - 10, centerY - 10);
    glEnd();
    //draw eyes
    glColor3f(0,.3,.5);
    glBegin(GL_TRIANGLE_FAN);
    int eyeX = centerX + 5;
    int eyeY = centerY - 6;
    glVertex2i(eyeX, eyeY);
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(eyeX  + (2.5  * cos(i)),
                   eyeY + (2.5 * sin(i)));
    }
    glEnd();
    //draw other eye
    glColor3f(0,.3,.5);
    glBegin(GL_TRIANGLE_FAN);
    int eye2X = centerX - 5;
    int eye2Y = centerY - 6;
    glVertex2i(eye2X, eye2Y);
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(eye2X  + (2.5 * cos(i)),
                   eye2Y + (2.5 * sin(i)));
    }
    glEnd();
    //smile
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLE_FAN);
    int smileX = centerX;
    int smileY = centerY - 2;
    glVertex2i(smileX, smileY);
    for (double i = 0; i < PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(smileX  + (2.5 * cos(i)),
                   smileY + (2.5 * sin(i)));
    }
    glEnd();
}

void DoodlePlayer::setColor(double r, double g, double b) {
    red = r;
    green = g;
    blue = b;
}


