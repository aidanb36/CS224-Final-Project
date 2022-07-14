#include "graphics.h"
#include "graphicsSnake.h"
#include "graphicsFlappyBird.h"
#include "graphicsHome.h"
#include "graphicsDoodle.h"
#include "graphicsBrickBreaker.h"


//#include "circle.h"
//#include "rect.h"
//#include "shape.h"
//#include <iostream>
//#include <memory>
//#include <vector>

using namespace std;

GLdouble widthM, heightM;
int wd;
enum arcade {home,flappy,snake,doodle,brick};
arcade arcadeGame;

void init() {
    widthM = 500;
    heightM = 500;
    arcadeGame = home;
    switch (arcadeGame){
        case home:
            initHome();
            break;
        case flappy:
            initFlappy();
            break;
        case snake:
            initSnake();
            break;
        case doodle:
            initDoodle();
            break;
        case brick:
            initBrickBreaker();
    }
}

/* Initialize OpenGL Graphics */
void initGL() {
    switch (arcadeGame){
        case home:
            initGLHome();
            break;
        case flappy:
            initFlappy();
            break;
        case snake:
            initGLSnake();
            break;
        case doodle:
            initGLDoodle();
            break;
        case brick:
            initGLBrickBreaker();
            break;
    }
    // Set "clearing" or background color
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    switch (arcadeGame){
        case home:
            displayHome();
            break;
        case flappy:
            displayFlappy();
            break;
        case snake:
            displaySnake2();
            break;
        case doodle:
            displayDoodle();
            break;
        case brick:
            displayBrickBreaker();
            break;
    }
    glFlush();  // Render now - Remember to take out glFlush in individual game cpp files so it doesn't flush twice - reduces lag
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    switch (arcadeGame){
        case home:
            kbdHome(key,x,y);
            break;
        case flappy:
            kbdFlappy(key,x,y);
            break;
        case snake:
            keyboardSnake(key,x,y);
            break;
        case doodle:
            kbdDoodle(key,x,y);
            break;
        case brick:
            kbdBrickBreaker(key,x,y);
            break;
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch (arcadeGame){
        case home:
            break;
        case flappy:
            break;
        case snake:
            keyboardSnake(key,x,y);
            break;
        case doodle:
            kbdSDoodle(key,x,y);
            break;
        case brick:
            kbdSBrickBreaker(key,x,y);
            break;
    }
    glutPostRedisplay();
}

void kbdSUp(int key, int x, int y){
    switch(arcadeGame){
        case doodle:
            kbdSUpDoodle(key,x,y);
    }
}

void cursor(int x, int y) {
    switch (arcadeGame){
        case home:
            cursorHome(x,y);
            break;
        case flappy:
            cursorFlappy(x,y);
            break;
        case snake:
            cursorSnake(x,y);
            break;
        case doodle:
            cursorDoodle(x,y);
            break;
        case brick:
            cursorBrickBreaker(x,y);
            break;
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    switch (arcadeGame){
        case home:

            mouseHome(button,state,x,y);
            if(mouseHome2(button,state,x,y)=="Flappy"){
                arcadeGame=flappy;
                initFlappy();
            }
            else if(mouseHome2(button,state,x,y)=="Snake"){
                arcadeGame=snake;
                initSnake();
            }
            else if(mouseHome2(button,state,x,y)=="Doodle"){
                arcadeGame=doodle;
                initDoodle();
            }
            else if(mouseHome2(button,state,x,y)=="Brick"){
                arcadeGame=brick;
                initBrickBreaker();
            }
            break;
        case flappy:
            mouseFlappy(button,state,x,y);
            if (getStateFlappy() == goHomeScreen){
                arcadeGame = home;
                initHome();
            }
            break;
        case snake:
            mouseSnake(button,state,x,y);
            if(getScreenSnake()==homeBB){
                arcadeGame=home;
                initHome();
            }
            break;
        case doodle:
            mouseDoodle(button,state,x,y);
            if (getStateDoodle() == goHomeScreenD){
                arcadeGame = home;
                initHome();
            }
            break;
        case brick:
            mouseBrickBreaker(button,state,x,y);
            if (getScreenBrick() == homeB){
                arcadeGame = home;
                initHome();
            }
            break;
    }
    glutPostRedisplay();
}




/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT
//    if(arcadeGame==snake){  //I don't think these will work because arcade game isn't chosen until glutMainLoop
//        init2Snake();       //Starts, which is at the end of main
//    }
    glutInitDisplayMode(GLUT_RGBA);

    if(arcadeGame!=snake){
        glutInitWindowSize((int)widthM, (int)heightM);
        glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
        /* create the window and store the handle to it */
        wd = glutCreateWindow("Arcade" /* title */ );
    }

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    //if(arcadeGame!=snake){
    initGL();
    //}

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);


    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    glutSpecialUpFunc(kbdSUp);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer - Add timer calls here

    glutTimerFunc(0, pipeTimerFlappy, 0);
//    glutTimerFunc(0, playerTimerFlappy, 0);

    glutTimerFunc(30, playerTimerDoodle, 0);
//    glutTimerFunc(30, tileTimerDoodle, 0);
//    glutTimerFunc(0, playerTimerXDoodle, 0);
//    glutTimerFunc(0, tileTimerXDoodle, 0);


    //for snake. Shouldn't need though because kbd called from kbds
    //glutKeyboardFunc(reinterpret_cast<void (*)(unsigned char, int, int)>(keyboardSnake));
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
