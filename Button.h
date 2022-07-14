//
// Created by Heshi Muntiu on 4/28/22.
//

#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H
#include "rect.h"
#include <string>
using namespace std;

class Button: public Rect{
private:
    string text;

public:
    //contructor
    Button(int x, int y, int w, int h, string t, double r, double g, double b);

    virtual void draw() const override;

    bool isOverlapping(int x, int y);

    void hover(color c);

    void press(color c);

    void release(color c);

    string getText();

    void setText(string t);

};

#endif //GAME_BUTTON_H
