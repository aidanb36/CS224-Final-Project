//
// Created by Xantia Kansil on 5/3/22.
//

#include "graphicsDoodle.h"
#include "Button.h"
#include "shape.h"
#include "DoodlePlayer.h"
#include "Tile.h"
//#include "graphics.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

GLdouble widthD, heightD;
int wdD;

DoodlePlayer userD(250,250);
int yVelD;
int xMove;
gameState g;
enum moveState {playerUp,tileDown,playerDown};
moveState sD;
enum xMoveState {left,right,stop};
xMoveState m;
vector<Tile>tiles;
int scoreD;
Button scoreButtonD(30,5,50,30,"0",1,1,1);
int tileDist;
bool movingTiles;
int pctMoving;
int movingSpeed;
Button newGameD(250,250,150,100,"New Game",0,.3,.41);
color hoverColorD(.2,.2,1);
color pressColorD(0,0,1);
color releaseColorD(0.3,0.4,1);
Button doodleJumpGame(250,75,200,70,"Doodle Jump",1,1,1);
Button gameOver(250,75,150,50,"Game Over",.8,0,0);
Button goHomeD(60,30,100,40,"Go Home",.5,.5,1);


string doodleJumpString;
string gameOverString;

gameState getStateDoodle(){
    return g;
}

void initDoodle() {
    widthD = 500;
    heightD = 500;
    srand(time(0));
    initTilesDoodle();
   // scoreButton.setColor(1,1,1);
    g = startD;
}

void initTilesDoodle(){
    scoreButtonD.setCenter(30,22);
    sD = playerDown;
    m = stop;
    tileDist = 15;
    movingTiles = false;
    movingSpeed = 0;
    pctMoving = 0;
    userD.moveX(1);
    tiles.clear();
    userD.setX(252);
    userD.setY(400);
    yVelD = -15;
    scoreD = 0;
    scoreButtonD.setText("0");
    int firstCenterX = 250;
    int firstCenterY = 400;
    tiles.push_back(Tile(firstCenterX,firstCenterY));
    tiles[0].setFillColor(0,1,0,1);
    for (int i =1; i < 20; i++){
        int randCenterX = rand() % 450 + 25;
        int randCenterY = tiles[i-1].getCenterY() - (rand() % 100 + tileDist);
        tiles.push_back(Tile(randCenterX,randCenterY));
    }
}

void initGLDoodle() {
    glClearColor(0, .76, 1, 1.0f);
}


void displayDoodle() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, widthD, heightD); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, widthD, heightD, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    switch (g){
        case startD:
            glClearColor(1, 1, 1, 1.0f);
            newGameD.draw();
            doodleJumpString = "Welcome to Doodle Jump!";
            doodleJumpGame.setText(doodleJumpString);
            doodleJumpGame.draw();
            break;

        case gameD:
            glClearColor(0, .76, 1, 1.0f);
            userD.draw();
            for(Tile &t :tiles){
                t.draw();
            }
            switch(sD){
                case playerUp:
                    if (userD.getCenterY() < 200){
                        sD = tileDown;
                    }
                    if (yVelD > 0){
                        sD = playerDown;
                    }
                    break;
                case tileDown:
                    if (yVelD > 0){
                        sD = playerDown;
                    }
                    break;
                case playerDown:
                    for(Tile &t :tiles){
                        if (userD.bounce(t,yVelD)){
                            yVelD = -17;
                            sD = playerUp;
                        }
                    }
                    break;
            }

            //player can move across the screen
            if (userD.getCenterX() < 0 && m == xMoveState::left){
                userD.setX(500);
            }
            else if (userD.getCenterX() > 500 && m == xMoveState::right){
                userD.setX(0);
            }
            scoreButtonD.draw();
            //check loss
            if (userD.getCenterY()> 500){
                g = gameState::endD;
            }
            break;

        case gameState::endD:
            glClearColor(0, 0, 0, 1.0f);
            gameOverString = "Game Over :(";
            gameOver.setText(gameOverString);
            gameOver.draw();
            scoreButtonD.setCenter(250,155);
            scoreButtonD.draw();
            newGameD.draw();
            goHomeD.draw();
            break;
    }
    //glFlush();  // Render now
}


// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbdDoodle(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wdD);
        exit(0);
    }
    //glutPostRedisplay();
}

void kbdSDoodle(int key, int x, int y) {
    if (g==gameD){
        switch(key){
            case GLUT_KEY_LEFT:
                m = xMoveState::left;
                break;
            case GLUT_KEY_RIGHT:
                m = xMoveState::right;
                break;
        }

    }

   // glutPostRedisplay();
}

void kbdSUpDoodle(int key, int x, int y){
    if (g==gameD){
        switch(key) {
            case GLUT_KEY_LEFT:
                m = stop;
                break;
            case GLUT_KEY_RIGHT:
                m = stop;
                break;
        }
    }
    //glutPostRedisplay();
}

void cursorDoodle(int x, int y) {
    //newgame button
    if(g == startD || g == gameState::endD){
        if (newGameD.isOverlapping(x,y)){
            newGameD.hover(hoverColorD);
        }
        else{
            newGameD.release(releaseColorD);
        }
    }
    //goHome button
    if (goHomeD.isOverlapping(x,y)){
        goHomeD.hover(hoverColorD);
    }
    else{
        goHomeD.release(releaseColorD);
    }
    //glutPostRedisplay();
}


void mouseDoodle(int button, int state, int x, int y) {
    if (g == startD) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && newGameD.isOverlapping(x, y)) {
            newGameD.press(pressColorD);
        } else {
            newGameD.release(releaseColorD);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && newGameD.isOverlapping(x, y)) {
            newGameD.hover(hoverColorD);
            g = gameD;
            //initTiles();
        }

    } else if (g == gameState::endD) {
        //for newGame button
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && newGameD.isOverlapping(x, y)) {
            newGameD.press(pressColorD);
        } else {
            newGameD.release(releaseColorD);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && newGameD.isOverlapping(x, y)) {
            newGameD.hover(hoverColorD);
            g = gameD;
            initTilesDoodle();
        }
        //for goHome button
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && goHomeD.isOverlapping(x, y)) {
            goHomeD.press(pressColorD);
        } else {
            goHomeD.release(releaseColorD);
        }
        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && goHomeD.isOverlapping(x, y)) {
            goHomeD.hover(hoverColorD);
            g = goHomeScreenD;
            goHomeD.release(releaseColorD);
        }
    }
    //glutPostRedisplay();
}


void playerTimerDoodle(int dummy) {
    if (g == gameState::gameD){
        //playerTimerDoodle
        if (sD == playerUp || sD == playerDown) {
            userD.moveY(yVelD);
        } else if (sD == tileDown) {
            scoreD -= yVelD;
            scoreButtonD.setText(to_string(scoreD));
            for (Tile &t: tiles) {
                t.moveY(-yVelD);

            }
        }
        yVelD++;
        //tileTimerDoodle
        int randCenterX = rand() % 450 + 25;
        if (scoreD < 2000){
            tileDist = 50;
        } else if (scoreD < 3000){
            tileDist = 60;
        } else if (scoreD < 3000){
            tileDist = 70;
            movingTiles = true;
            pctMoving = 20;
            movingSpeed = 1;
        } else if (scoreD < 5000){
            movingTiles = true;
            pctMoving = 40;
            movingSpeed = 2;
        }else if (scoreD < 6000){
            movingTiles = true;
            pctMoving = 50;
            movingSpeed = 3;
        }else if (scoreD < 7000){
            movingTiles = true;
            pctMoving = 70;
            movingSpeed = 4;
        }
        for (int i = 0; i < tiles.size(); i++){
            if (tiles[i].getTopY() > 500){
                if (i == 0){
                    int randCenterY = tiles[19].getCenterY() - (rand() % 100 + tileDist);
                    tiles[i].setCenter(randCenterX,randCenterY);
                } else{
                    int randCenterY = tiles[i - 1].getCenterY() - (rand() % 100 + tileDist);
                    tiles[i].setCenter(randCenterX,randCenterY);
                }
                if (movingTiles){
                    int movingChance = rand() % 100;
                    if (movingChance < pctMoving){
                        tiles[i].setXMoving(true);
                        tiles[i].setDirection(0);
                    } else {
                        tiles[i].setXMoving(false);
                    }
                }
            }
        }
        //playerTimerXDoodle
        switch (m) {
            case xMoveState::left:
                xMove -= 1;
                break;
            case xMoveState::right:
                xMove += 1;
                break;
            case xMoveState::stop:
                xMove = xMove/1.4;
                break;
        }
        userD.moveX(xMove);
        //tileTimerXDoodle
        for (Tile &t: tiles) {
            if (t.getXMoving()) {
                switch (t.getDirection()) {
                    case 0: // left
                        t.moveX(-movingSpeed);
                        if (t.getCenterX() < 0) {
                            t.setDirection(1);
                        }
                        break;

                    case 1: //right
                        t.moveX(movingSpeed);
                        if (t.getCenterX() > 500) {
                            t.setDirection(0);
                        }
                        break;
                }
            }
        }
        glutPostRedisplay();
    }
    glutTimerFunc(30, playerTimerDoodle, dummy);

}

//void tileTimerDoodle(int dummy) {
//    int randCenterX = rand() % 450 + 25;
//    if (scoreD < 2000) {
//        tileDist = 50;
//    } else if (scoreD < 3000) {
//        tileDist = 60;
//    } else if (scoreD < 3000) {
//        tileDist = 70;
//        movingTiles = true;
//        pctMoving = 20;
//        movingSpeed = 1;
//    } else if (scoreD < 5000) {
//        movingTiles = true;
//        pctMoving = 40;
//        movingSpeed = 2;
//    } else if (scoreD < 6000) {
//        movingTiles = true;
//        pctMoving = 50;
//        movingSpeed = 3;
//    } else if (scoreD < 7000) {
//        movingTiles = true;
//        pctMoving = 70;
//        movingSpeed = 4;
//    }
//    for (int i = 0; i < tiles.size(); i++) {
//        if (tiles[i].getTopY() > 500) {
//            if (i == 0) {
//                int randCenterY = tiles[19].getCenterY() - (rand() % 100 + tileDist);
//                tiles[i].setCenter(randCenterX, randCenterY);
//            } else {
//                int randCenterY = tiles[i - 1].getCenterY() - (rand() % 100 + tileDist);
//                tiles[i].setCenter(randCenterX, randCenterY);
//            }
//            if (movingTiles) {
//                int movingChance = rand() % 100;
//                if (movingChance < pctMoving) {
//                    tiles[i].setXMoving(true);
//                    tiles[i].setDirection(0);
//                } else {
//                    tiles[i].setXMoving(false);
//                }
//            }
//        }
//    }
//    glutPostRedisplay();
//    glutTimerFunc(30, tileTimerDoodle, dummy);
//
//
//}
//
//void playerTimerXDoodle(int dummy) {
//    switch (m) {
//        case xMoveState::left:
//            xMove -= 1;
//            break;
//        case xMoveState::right:
//            xMove += 1;
//            break;
//        case xMoveState::stop:
//            xMove = 0;
//            break;
//    }
//    userD.moveX(xMove);
//
//    glutPostRedisplay();
//    glutTimerFunc(0, playerTimerXDoodle, dummy);
//
//
//}
//
//void tileTimerXDoodle(int dummy) {
//    for (Tile &t: tiles) {
//        if (t.getXMoving()) {
//            switch (t.getDirection()) {
//                case 0: // left
//                    t.moveX(-movingSpeed);
//                    if (t.getCenterX() < 0) {
//                        t.setDirection(1);
//                    }
//                    break;
//
//                case 1: //right
//                    t.moveX(movingSpeed);
//                    if (t.getCenterX() > 500) {
//                        t.setDirection(0);
//                    }
//                    break;
//            }
//        }
//    }
//    glutPostRedisplay();
//    glutTimerFunc(20, tileTimerXDoodle, dummy);
//
//}


//int main(int argc, char** argv){
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
//    wd = glutCreateWindow("Doodle Jump");
//
//    glutDisplayFunc(display);
//
//    initGL();
//
//    glutKeyboardFunc(kbd);
//
//    glutSpecialFunc(kbdS);
//
//    glutSpecialUpFunc(kbdSUp);
//
//    glutPassiveMotionFunc(cursor);
//
//    glutMouseFunc(mouse);
//
//    glutTimerFunc(30, playerTimerDoodle, 0);
//    glutTimerFunc(30, tileTimerDoodle, 0);
//    glutTimerFunc(0, playerTimerXDoodle, 0);
//    glutTimerFunc(0, tileTimerXDoodle, 0);
//
//    glutMainLoop();
//    return 0;
//}
//
