//
// Created by Xantia Kansil on 4/28/22.
//

#include "Pipe.h"
#include <iostream>
#include "graphics.h"
using namespace std;

Pipe::Pipe(int cX, int cY) {
    centerY = cY;
    centerX = cX;
}

void Pipe::moveLeft() {
    centerX -= 5;
}

void Pipe::draw() {
    //set the color to the fill field
    glColor3f(0, 1,0);
    //draw quad
    glBegin(GL_QUADS);
    glVertex2i(centerX - 25, centerY + 65);
    glVertex2i(centerX + 25, centerY+65);
    glVertex2i(centerX+25, 500);
    glVertex2i(centerX - 25, 500);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(centerX - 25, centerY - 65);
    glVertex2i(centerX + 25, centerY - 65);
    glVertex2i(centerX + 25, 0);
    glVertex2i(centerX - 25, 0);
    glEnd();

}

int Pipe::getCenterX() {
    return centerX;
}

int Pipe::getLeftX() {
    return centerX - 25;
}

int Pipe::getRightX() {
    return centerX + 25;
}

int Pipe::getCenterY() {
    return centerY;
}

int Pipe::getBottomY() {
    return centerY - 65;
}

int Pipe::getTopY() {
    return centerY + 65;
}

void Pipe::setCenterX(int x){
    centerX = x;
}

void Pipe::setCenterY(int y) {
    centerY = y;
}