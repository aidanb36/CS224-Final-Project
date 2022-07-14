//
// Created by Xantia Kansil on 4/28/22.
//


#include "graphics.h"
#include "Player.h"
#include "pipe.h"
#include <cmath>
#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;


Player::Player(int x, int y) {
    centerX = x;
    centerY = y;
    red = 1;
    green = 0;
    blue = 0;
}

void Player::moveY(int y) {
    centerY += y;
}


void Player::setX(int x) {
    centerX = x;
}

void Player::setY(int y){
    centerY = y;
}

bool Player::hitPipe(Pipe p) {
    for (double theta = 0; theta < 2 * PI;theta += .25 ){
        double xCord = centerX + radius * cos(theta);
        double yCord = centerY + radius * sin(theta);

        if ((xCord > p.getLeftX() && centerX < p.getCenterX()) || (xCord < p.getRightX() && centerX > p.getCenterX()) ) {
            if (yCord < p.getBottomY() || yCord > p.getTopY()){
                return true;
            }

        }
    }
    return false;
}

bool Player::passPipe(Pipe p) {
    if(centerX - 20 == p.getRightX()){
        return true;
    }else{
        return false;
    }
}

void Player::draw()  {
    //draw circle
    glColor3f(red,green,blue);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(centerX, centerY);
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(centerX + (radius * cos(i)),
                   centerY + (radius * sin(i)));
    }
    glEnd();
    //draw beak
    glColor3f(1,1,0);
    glBegin(GL_TRIANGLES);
    glVertex2i(centerX + radius,centerY);
    glVertex2i(centerX + radius * cos(PI/6),centerY - radius * sin(PI/6));
    glVertex2i(centerX + radius + 10,centerY - radius * sin(PI/6));
    glEnd();
    //draw eye
    glColor3f(0,.2,.5);
    glBegin(GL_TRIANGLE_FAN);
    int eyeX = centerX + 3;
    int eyeY = centerY - 3;
    glVertex2i(eyeX, eyeY);
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(eyeX  + (5 * cos(i)),
                   eyeY + (5 * sin(i)));
    }
    glEnd();
}

void Player::setColor(double r, double g, double b) {
    red = r;
    green = g;
    blue = b;
}


