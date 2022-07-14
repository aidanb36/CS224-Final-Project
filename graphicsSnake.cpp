#include <ctime>
#include <deque>
#include "graphicsSnake.h"
#include "circle.h"
#include "rect.h"
#include "graphics.h"


//found this online, should remove risk messages from glut
#define UNUSED(param) (void)(param)

screens scree;

//color constants
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color magenta(1, 0, 1);

// snake directions
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

//title and width and height
GLdouble width, height;
char title[] = "Snake Game";

//rectangle snak and yum(food)
Rect snak;
Rect yum;

//user for mouse
Rect user;

//difficulty rects
Rect easy(white,100,-100);
Rect med(white,250,-100);
Rect hard(white,400,-100);

//circle for ring around food
Circle tasty(white,1,1,7);

//half the length of the perspective
float map_half_length = 30.0f;

//initialize the direction, move speed, xy coordinates
int direction = DOWN;
int move_speed = 100;
bool moved = false;

//found this in research, allows to pop off front and back, useful
std::deque< std::deque<float> > snake_xy;

//two food
int food_xy[2];

//set available food to false
bool food_available = false;

screens getScreenSnake(){
    return scree;
}

//user initials, and difficulties for ease
void initUserSnake() {
    user.setCenter(50, 450);
    user.setSize(10, 10);
    easy.setCenter(100,250);
    easy.setSize(50,50);
    med.setCenter(250,250);
    med.setSize(50,50);
    hard.setCenter(400,250);
    hard.setSize(50,50);
    user.setFillColor(brickRed);
}

//init
void initSnake() {
    width = 500;
    height = 500;
    srand(time(0));
    initUserSnake();
}


//init gl
void initGLSnake(){
    glMatrixMode(GL_PROJECTION);
    gluPerspective(75.0f, 1, 0.0f, 35.0f);
    srand(time(0));
    width = 600;
    height = 600;
}


//food, works by using a temporary coordinate for the food, and mapping it to the window
//sees if the snake collides with the food
void food(){
    if(!food_available){
        while(true){
            bool collides = false;
            //temporary random coordinate
            int temp_food_coords[2] = { food_xy[0] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length,
                    food_xy[1] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length };

            //collision
            for(unsigned int a = 0; a < snake_xy.size(); a++){
                if(temp_food_coords[0] == snake_xy[a][0] &&
                   temp_food_coords[1] == snake_xy[a][1]){
                    collides = true;
                }
            }
            // If it doesn't collide with the snake, then make it the real food coordinates
            if(collides == false){
                food_xy[0] = temp_food_coords[0];
                food_xy[1] = temp_food_coords[1];
                food_available = true;
                break;
            }
        }
    }
}

//this displays the snake and the food, display 2 handles the initial window
void displaySnake(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    tasty.draw();
    //snake
    for(unsigned int a = 0; a < snake_xy.size(); a++){
        glLoadIdentity();
        glTranslatef(snake_xy[a][0], snake_xy[a][1], -40.0f);
        dimensions sna;
        sna.height=1;
        sna.width=1;
        snak.setCenter(food_xy[0]-40, food_xy[1]-40);
        snak.setFillColor(magenta);
        snak.draw3();
    }

    //food
    glLoadIdentity();
    glTranslatef(food_xy[0], food_xy[1], -40.0f);
    dimensions yummy;
    yummy.height=1;
    yummy.width=1;
    yum.setCenter(food_xy[0]-40, food_xy[1]-40);
    yum.setFillColor(brickRed);
    yum.draw3();

    food();
    glutSwapBuffers();
}

//moves the snake, takes in a direction as int (1,2,3,4)
int growth_stage = 0;
int growth = 2;
void move(int new_direction){
    direction = new_direction;
    int last_part = snake_xy.size() - 1;
    std::deque<float> new_head = snake_xy[last_part];

    if(direction == UP){
        //slither into itself
        for(unsigned int a = 0; a < snake_xy.size(); a++){
            if(snake_xy[0][0]== snake_xy[a][0] &&
               snake_xy[0][1] + 2.0f == snake_xy[a][1]){
                scree = homeBB;
                exit(0);
               // scree = homeBB;
            }
        }

        //slither into wall
        if(snake_xy[0][1] == map_half_length){
            scree = homeBB;
            //init2Snake();
            //glutDestroyWindow();
            exit(0);
        }

        //food
        if(snake_xy[0][0] == food_xy[0] &&
           snake_xy[0][1] + 2.0f == food_xy[1]){
            growth_stage++;
            food_available = false;
            glClearColor(.5,rand()%2,rand()%2,1.0);

        }

        new_head[1] = snake_xy[0][1] + 2.0f;
    } else if(direction == DOWN){
        //slither into itself
        for(unsigned int a = 0; a < snake_xy.size(); a++){
            if(snake_xy[0][0] == snake_xy[a][0] &&
               snake_xy[0][1] - 2.0f == snake_xy[a][1]){
                scree = homeBB;
                exit(0);
            }
        }

        //slither into wall
        if(snake_xy[0][1] == -map_half_length){
            scree = homeBB;
            exit(0);
        }

        //food
        if(snake_xy[0][0]== food_xy[0] &&
           snake_xy[0][1] - 2.0f == food_xy[1]){
            growth_stage++;
            food_available = false;
            glClearColor(.5,rand()%2,rand()%2,1.0);
        }

        new_head[1] = snake_xy[0][1] - 2.0f;
    } else {
        new_head[1] = snake_xy[0][1];
    }

    if(direction == LEFT){
        //slither into self
        for(unsigned int a = 0; a < snake_xy.size(); a++){
            if(snake_xy[0][0] - 2.0f == snake_xy[a][0] &&
               snake_xy[0][1] == snake_xy[a][1]){
                scree = homeBB;
                exit(0);
            }
        }
        //slither into self
        if(snake_xy[0][0] == -map_half_length){
            scree = homeBB;
            exit(0);
        }
        //food
        if(snake_xy[0][0] - 2.0f == food_xy[0] &&
           snake_xy[0][1]        == food_xy[1]){
            growth_stage++;
            food_available = false;
            glClearColor(.5,rand()%2,rand()%2,1.0);
        }
        new_head[0] = snake_xy[0][0] - 2.0f;

    } else if(direction == RIGHT){
        //slither into self
        for(unsigned int a = 0; a < snake_xy.size(); a++){
            if(snake_xy[0][0] + 2.0f == snake_xy[a][0] &&
               snake_xy[0][1] == snake_xy[a][1]){
                scree = homeBB;
                exit(0);
            }
        }

        //slither into a wall
        if(snake_xy[0][0] == map_half_length){
            scree = homeBB;
            exit(0);
        }
        scree=homeBB;

        //food
        if(snake_xy[0][0] + 2.0f == food_xy[0] &&
           snake_xy[0][1] == food_xy[1]){
            growth_stage++;
            food_available = false;
            glClearColor(.3,rand()%2,rand()%2,1.0);
        }
        new_head[0] = snake_xy[0][0] + 2.0f;
    } else {
        new_head[0] = snake_xy[0][0];
    }

    snake_xy.push_front(new_head);

    if(!growth_stage){
        snake_xy.pop_back();
    } else if(growth_stage == growth){
        growth_stage = 0;
    } else {
        growth_stage++;
    }
    //glutPostRedisplay();
}

//timer for move snake, on its own
void timerSnake(int value){
    if(!moved){
        UNUSED(value);
        if(direction == UP){
            move(UP);
        } else if(direction == DOWN){
            move(DOWN);
        } else if(direction == LEFT){
            move(LEFT);
        } else if(direction == RIGHT){
            move(RIGHT);
        }
    } else {
        moved = false;
    }

    glutTimerFunc(move_speed, timerSnake, 0);
}

//makes sure the window stays consistent
void reshape(GLsizei width, GLsizei height){
    UNUSED(width);
    UNUSED(height);
    glutReshapeWindow(600, 600);
}

//init 2 for second window
void init2Snake(){
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,200);
    glutCreateWindow("Simple Window");
}

//keyboard for up, down, left, right
void keyboardSnake(int key, int x, int y){
    UNUSED(x);
    UNUSED(y);
    switch(key){
        case GLUT_KEY_UP:{
            if(direction == LEFT || direction == RIGHT){
                moved = true;
                move(UP);
            }
            break;
        }

        case GLUT_KEY_DOWN:{
            if(direction == LEFT || direction == RIGHT){
                moved = true;
                move(DOWN);
            }
            break;
        }

        case GLUT_KEY_LEFT:{
            if(direction == UP || direction == DOWN){
                moved = true;
                move(LEFT);
            }
            break;
        }

        case GLUT_KEY_RIGHT:{
            if(direction == UP || direction == DOWN){
                moved = true;
                move(RIGHT);
            }
            break;
        }
    }
    if (key == 115) {

    }

    //glutPostRedisplay();
}



//second display, with is overlapping with the user
void displaySnake2()
{
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, 500, 500);
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500, 500, 0.0, -1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    user.draw();

    //easy
    if(easy.isOverlapping(user)){
        move_speed = 200;
        //glutInit(&argc, argv);
        glutInitWindowSize(600, 600);
        glutCreateWindow(title);
        glutDisplayFunc(displaySnake);
        glutReshapeFunc(reshape);
        glutSpecialFunc(keyboardSnake);
        glutTimerFunc(move_speed, timerSnake, 0);
        int initSize = 3;
        // coordinates
        for(int a = 1; a <= initSize; a++){
            std::deque<float> row;
            row.push_back(0.0f);
            row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));
            snake_xy.push_front(row);
        }

        srand(time(NULL));
        //InitFood();
        initGLSnake();
        //glutMainLoop();
    }

    //medium
    if(med.isOverlapping(user)){
        move_speed = 100;
        //glutInit(&argc, argv);
        glutInitWindowSize(600, 600);
        glutCreateWindow(title);
        glutDisplayFunc(displaySnake);
        glutReshapeFunc(reshape);
        glutSpecialFunc(keyboardSnake);
        glutTimerFunc(move_speed, timerSnake, 0);
        int initSize = 3;

        // coordinates
        for(int a = 1; a <= initSize; a++){
            std::deque<float> row;
            row.push_back(0.0f);
            row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));
            snake_xy.push_front(row);
        }

        srand(time(NULL));

        //InitFood();
        initGLSnake();
        //glutMainLoop();
    }

    //hard
    if(hard.isOverlapping(user)){
        move_speed = 50;
        //glutInit(&argc, argv);
        glutInitWindowSize(600, 600);
        glutCreateWindow(title);
        glutDisplayFunc(displaySnake);
        glutReshapeFunc(reshape);
        glutSpecialFunc(keyboardSnake);
        glutTimerFunc(move_speed, timerSnake, 0);
        int initSize = 3;

        // coordinates
        for(int a = 1; a <= initSize; a++){
            std::deque<float> row;
            row.push_back(0.0f);
            row.push_back((map_half_length + 2.0f + (initSize * 2)) - (a * 2));
            snake_xy.push_front(row);
        }

        srand(time(NULL));

        //InitFood();
        initGLSnake();
        //glutMainLoop();
    }

    //welcome to snake game
    glColor3f(1, 0, 0);
    glRasterPos2i(180,75);
    for (const char &letter : "Welcome to Snake!") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    //drawing the different difficulties
    glColor3f(0, 1, 0);
    glRasterPos2i(180,175);
    for (const char &letter : "Select Difficulty") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    glColor3f(0, 1, 0);
    glRasterPos2i(100,250);
    for (const char &letter : "easy") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
    glColor3f(0, 1, 0);
    glRasterPos2i(225,250);
    for (const char &letter : "medium") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
    glColor3f(0, 1, 0);
    glRasterPos2i(365,250);
    for (const char &letter : "hard") {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }

    //glFlush();
}

//cursor
void cursorSnake(int x, int y) {
    user.setCenter(x,y);
    //glutPostRedisplay();
}


//mouse
void mouseSnake(int button, int state, int x, int y) {
    //glutPostRedisplay();
}

//main
//int main(int argc, char** argv){
//
//    initSnake();
//    //start window
//    glutInit(&argc,argv);
//    init2Snake();
//
//    // handles mouse movement
//    glutPassiveMotionFunc(cursorSnake);
//
//    // handles mouse click
//    glutMouseFunc(mouseSnake);
//    glutDisplayFunc(displaySnake2);
//    glutKeyboardFunc(reinterpret_cast<void (*)(unsigned char, int, int)>(keyboardSnake));
//    glutMainLoop();
//
//
//    return 0;
//}