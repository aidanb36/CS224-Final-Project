//
// Created by Xantia Kansil on 4/28/22.
//


//#include "graphics.h"
#include "graphicsFlappyBird.h"
#include "Pipe.h"
#include "Player.h"
#include "Button.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string>
using namespace std;

GLdouble widthF, heightF;
int wdF;

vector<Pipe>pipes;
int pipeDistance;
Player player(250,250);
state s;

//vector<Button>buttons{Button(125,200,100,50,"Easy",.5,.5,1), Button(250,200,100,50,"Medium",.5,.5,1), Button(375,200,100,50,"Hard",.5,.5,1) };
vector<Button>buttons;
Button newGame(250,250,200,100,"New Game",.5,.5,1);
Button goHome(60,30,100,40,"Go Home",.5,.5,1);
Button scoreButton(50,50,80,30,"score: ",.5,.5,1);
Button levelButton(50,20,80,20,"Level: ",.5,.5,1);
Button flappyBirdGame(250,75,200,70,"Flappy Bird! ",1,1,1);

int yVel;
int hitTime;
int score;
string scoreString;
string levelString;
string flappyBirdString;
//button colors:
color releaseColor(.5,.5,1);
color hoverColor(.3,.3,1);
color pressColor(0,0,1);
//Button leaderboardFlappy (250,400,150,55,"View Leaderboard",.5,.5,1);

state getStateFlappy(){
    return s;
}

void initFlappy() {
    widthF = 500;
    heightF = 500;
    srand(time(0));
    buttons.push_back(Button(125,200,100,50,"Easy",.5,.5,1));
    buttons.push_back(Button(250,200,100,50,"Medium",.5,.5,1));
    buttons.push_back(Button(375,200,100,50,"Hard",.5,.5,1));
    s = start;
}

void initPipesFlappy(int dist){
    pipeDistance = dist;
    pipes.clear();
    int centerX = 600;
    for (int i = 0; i<5; i++){
        int randCenterY = rand() % 300 + 100;
        pipes.push_back(Pipe(centerX, randCenterY));
        centerX += pipeDistance;
    }
}

void initGLFlappy() {
    glClearColor(0, 0, 0, 1.0f);
}


void displayFlappy() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, widthF, heightF); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, widthF, heightF, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    if (s == start){
        glClearColor(1, 1, 1, 1.0f);
        score = 0;
        yVel = -10;
        hitTime = 0;
        scoreButton.setCenter(50,50);

        flappyBirdString = "Welcome to Flappy Bird!";
        flappyBirdGame.setText(flappyBirdString);
        flappyBirdGame.draw();

        player.setColor(1,0,0);
        for (Button &b:buttons){
            b.draw();
        }
//        leaderboardFlappy.draw();
    } else if (s == game){
        glClearColor(0, .72, 1, 1.0f);
        //draw pipes
        for (Pipe &p : pipes){
            p.draw();
        }
        //draw player
        player.draw();
        //check hit
        for (Pipe &p : pipes){
            if (player.hitPipe(p)){
                s = hit;
            }
        }
        for (Pipe &p : pipes){
            if (player.passPipe(p)){
                score ++;
            }
        }
        //draw score
        scoreString = "score: " + to_string(score/2);
        scoreButton.setText(scoreString);
        scoreButton.draw();
        levelButton.setText(levelString);
        levelButton.draw();

    } else if (s == hit){
        glClearColor(0, .72, 1, 1.0f);
        player.setColor(1,.5,.5);
        //draw pipes
        for (Pipe &p : pipes){
            p.draw();
        }
        //draw player
        player.draw();
        hitTime ++;
        if (hitTime > 100){
            s = over;
        }
        //draw score
        scoreButton.draw();
        levelButton.draw();
    }else if (s == over){
        glClearColor(0, 0, 0, 1.0f);
        scoreButton.setCenter(250,100);
        scoreButton.draw();
        newGame.draw();
        goHome.draw();
        player.setY(250);
        for (Button &b : buttons){
            b.release(releaseColor);
        }

    }

    //glFlush();  // Render now
}


// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbdFlappy(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wdF);
        exit(0);
    }
    //space bar
    switch(key) {
        case 32:
            yVel = -10;
            break;
    }

    //glutPostRedisplay();
}



void cursorFlappy(int x, int y) {
    if(s == start){
        for(Button &b : buttons){
            if (b.isOverlapping(x,y)){
                b.hover(hoverColor);
            }
            else{
                b.release(releaseColor);
            }
        }
    } else if (s == over){
        //for newGame button
        if (newGame.isOverlapping(x,y)){
            newGame.hover(hoverColor);
        }
        else{
            newGame.release(releaseColor);
        }
        //for goHome Button
        if (goHome.isOverlapping(x,y)){
            goHome.hover(hoverColor);
        }
        else{
            goHome.release(releaseColor);
        }
    }
    glutPostRedisplay();
}


void mouseFlappy(int button, int state, int x, int y) {
    if(s == start) {
        for (int i = 0; i<buttons.size();i++){
            if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && buttons[i].isOverlapping(x, y)) {
                buttons[i].press(pressColor);
            } else {
                buttons[i].release(releaseColor);
            }
            if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && buttons[i].isOverlapping(x, y)) {
                buttons[i].hover(hoverColor);
                switch (i){
                    case 0:
                        initPipesFlappy(350);
                        levelString = "easy";
                        break;
                    case 1:
                        initPipesFlappy(275);
                        levelString = "medium";

                        break;
                    case 2:
                        initPipesFlappy(215);
                        levelString = "hard";

                        break;
                }
                s = game;
            }
        }
    } else if (s == over){
        //for newGame button
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && newGame.isOverlapping(x, y)) {
            newGame.press(pressColor);
        } else {
            newGame.release(releaseColor);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && newGame.isOverlapping(x, y)) {
            newGame.hover(hoverColor);
            s = start;
        }

        //for goHome button
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && goHome.isOverlapping(x, y)) {
            goHome.press(pressColor);
        } else {
            goHome.release(releaseColor);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && goHome.isOverlapping(x, y)) {
            goHome.hover(hoverColor);
            s = goHomeScreen;
            buttons.clear();
            goHome.release(releaseColor);
        }
    }
    glutPostRedisplay();
}


void pipeTimerFlappy(int dummy) {
    if (s == game){
        int randCenterY = rand() % 250 + 150;
        for (int i =0; i< pipes.size();i++){
            pipes[i].moveLeft();
            if (pipes[i].getRightX() < 0 ){
                if (i == 0){
                    pipes[i].setCenterX(pipes[4].getCenterX()+pipeDistance);
                } else {
                    pipes[i].setCenterX(pipes[i-1].getCenterX()+pipeDistance);
                }
                pipes[i].setCenterY(randCenterY);
            }
        }
    }
    if (s == game){
        player.moveY(yVel);
        yVel ++;
    }

    glutPostRedisplay();
    glutTimerFunc(30, pipeTimerFlappy, dummy);
}

//void playerTimerFlappy(int dummy) {
//    if (s == game){
//        player.moveY(yVel);
//        yVel ++;
//    }
//    glutPostRedisplay();
//    glutTimerFunc(30, playerTimerFlappy, dummy);
//}

//int main(int argc, char** argv) {
//    srand(time(0));
//
//    init();
//
//    glutInit(&argc, argv);
//
//    glutInitDisplayMode(GLUT_RGBA);
//
//    glutInitWindowSize((int)width, (int)height);
//
//    glutInitWindowPosition(100, 200);
//
//    wd = glutCreateWindow("Flappy Bird!");
//
//    glutDisplayFunc(display);
//
//    initGLFlappy();
//
//    glutKeyboardFunc(kbd);
//
//    glutPassiveMotionFunc(cursor);
//
//    glutMouseFunc(mouse);
//
//    glutTimerFunc(0, pipeTimer, 0);
//
//    glutTimerFunc(0, playerTimer, 0);
//
//
//    // Enter the event-processing loop
//    glutMainLoop();
//    return 0;
//}

