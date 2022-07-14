//
// Created by Xantia Kansil on 4/28/22.
//

#ifndef GAME_PIPE_H
#define GAME_PIPE_H


class Pipe{
private:
    int centerY;
    int centerX;
public:
    //contructor
    Pipe(int cX, int cY);

    //getters
    int getCenterX();
    int getLeftX();
    int getRightX();
    int getCenterY();
    int getTopY();
    int getBottomY();

    //setters
    void setCenterX(int x);
    void setCenterY(int y);

    void moveLeft();

    void draw();

    //destructor
    virtual ~Pipe() = default;




};





#endif //GAME_PIPE_H
