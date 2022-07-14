
#include "Button.h"
#include "graphics.h"

Button::Button(int x, int y, int w, int h, string t, double r, double g, double b):Rect(color(r,g,b,1),point2D(x,y),dimensions(w,h)) {
    text = t;

}

void Button::draw() const {
    Rect::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * text.length()), center.y + 7);
    for (const char &letter : text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

bool Button::isOverlapping(int x, int y) {
    if (((x > center.x - size.width/2) && (x < center.x + size.width/2)) && ((y > center.y - size.height/2) && (y < center.y + size.height/2))){
        return true;

    }
    return false;
}

void Button::hover(color c) {
    setFillColor(c);
}

void Button::press(color c) {
    setFillColor(c);
}

void Button::release(color c) {
    setFillColor(c);
}

string Button::getText() {
    return text;
}

void Button::setText(string t) {
    text = t;
}
