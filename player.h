//
// Created by Xantia Kansil on 4/28/22.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H


#include "Pipe.h"

class Player{
private:
    int centerX;
    int centerY;
    double radius = 20;
    double red;
    double green;
    double blue;
public:
    //constructor
    Player(int x, int y);


    void setX(int x);
    void setY(int y);

    void moveY(int y);

    void draw();

    bool hitPipe(Pipe p);

    bool passPipe(Pipe p);

    void setColor(double r, double g, double b);
};





#endif //GAME_PLAYER_H
