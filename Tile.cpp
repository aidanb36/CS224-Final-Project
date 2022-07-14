//
// Created by Heshi Muntiu on 5/1/22.
//

#include "Tile.h"
#include "graphics.h"

Tile::Tile(int cX, int cY):Rect(point2D(cX,cY),dimensions(50,10)) {
    setFillColor(color(0,1,0));
    xMoving = false;
}


void Tile::move() {
}

void Tile::setXMoving(bool move) {
    xMoving = move;
}

bool Tile::getXMoving() {
    return xMoving;
}

void Tile::setDirection(int d) {
    direction = d;
}
int Tile::getDirection() {
    return direction;
}
