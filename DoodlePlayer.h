//
// Created by Heshi Muntiu on 5/1/22.
//

#ifndef DOODLEJUMP_DOODLEPLAYER_H
#define DOODLEJUMP_DOODLEPLAYER_H
#include "Tile.h"

class DoodlePlayer{
private:
    int centerX;
    int centerY;
    double red;
    double green;
    double blue;
public:
    //constructor
    DoodlePlayer(int x, int y);


    void setX(int x);
    void setY(int y);

    int getCenterY();
    int getCenterX();


    void moveX(int x);
    void moveY(int y);

    void draw();

    bool bounce(Tile t, int vel);

    void setColor(double r, double g, double b);
};


#endif //DOODLEJUMP_DOODLEPLAYER_H
