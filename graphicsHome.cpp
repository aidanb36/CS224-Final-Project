//
// Created by aidan on 5/2/2022.
//

#include "graphicsHome.h"
#include "Button.h"
//#include "graphics.h"
//#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
int wdf;
GLdouble wid, hei;
vector<Button>starter{Button(125,200,100,50,"Flappy",.5,.5,1), Button(250,200,100,50,"Snake",.5,.5,1), Button(375,200,100,50,"Doodle Jump",.5,.5,1), Button(250,300,120,50,"Brick Breaker",.5,.5,1) };
color hoverCol(.8,.3,1);
color releaseCol(.8,.5,1);
color pressCol(.8,.3,1);
string game;

void initHome(){
    wid = 500;
    hei = 500;
    srand(time(0));
    for (Button &b: starter){
        b.release(releaseCol);
    }
    game = "";
}

//init gl
void initGLHome(){
    glMatrixMode(GL_PROJECTION);
    //gluPerspective(75.0f, 1, 0.0f, 35.0f);
    srand(time(0));
    wid = 500;
    hei = 500;
}

void displayHome() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, wid, hei); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, wid, hei, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    glClearColor(0, 0, 0, 1.0f);
    for (Button &a: starter) {
        a.draw();
    }
}


// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbdHome(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wdf);
        exit(0);
    }
    //glutPostRedisplay();
}

void cursorHome(int x, int y){
    for(Button &b : starter){
        if (b.isOverlapping(x,y)){
            b.hover(hoverCol);
        }
        else{
            b.release(releaseCol);
        }
    }
    //glutPostRedisplay();
}

void mouseHome(int button, int state, int x, int y){
    for (int i = 0; i<starter.size();i++){
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && starter[i].isOverlapping(x, y)) {
            starter[i].press(pressCol);
        } else {
            starter[i].release(releaseCol);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && starter[i].isOverlapping(x, y)) {
            starter[i].hover(hoverCol);
        }
    }
    //glutPostRedisplay();
}

string mouseHome2(int button, int state, int x, int y){
    for (int i = 0; i<starter.size();i++){
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && starter[i].isOverlapping(x, y)) {
            starter[i].press(pressCol);
        } else {
            starter[i].release(releaseCol);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && starter[i].isOverlapping(x, y)) {
            starter[i].hover(hoverCol);
            switch (i){
                case 0:
                    game = "Flappy";
                    break;
                case 1:
                    game = "Snake";
                    break;
                case 2:
                    game = "Doodle";
                    break;
                case 3:
                    game = "Brick";
                    break;
            }
        }
    }
    //glutPostRedisplay();
    return game;
}
