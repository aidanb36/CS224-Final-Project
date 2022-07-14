//
// Created by Heshi Muntiu on 5/1/22.
//

#ifndef DOODLEJUMP_TILE_H
#define DOODLEJUMP_TILE_H

#include "rect.h"

class Tile : public Rect{
private:
    bool xMoving;
    int direction;
public:
    //contructor
    Tile(int cX, int cY);

    void move();

    //destructor
    virtual ~Tile() = default;

    void setXMoving(bool move);
    bool getXMoving();

    void setDirection(int d);
    int getDirection();


};

#endif //DOODLEJUMP_TILE_H
