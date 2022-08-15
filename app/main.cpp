#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "../include/game.hpp"
#include "../include/draw.hpp"

Game game;
Draw draw;
int _w, _h;

// display callback function that handles rendering of the game
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // render the game board
    game.draw();

    glutSwapBuffers();
    glFlush();
}

// reshape callback function that allows for dynamic resizing of the viewport
// while not affecting user interactions with game board
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game.getColumns() * draw.getCellSize(), game.getRows() * draw.getCellSize(), 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    _w = w;
    _h = h;
}

// mouse function that determines how a user can interact with the game via mouse clicks
void mouse(int button, int state, int x, int y)
{
    // once mouse click has been pressed and released
    if (state == GLUT_UP)
    {
        switch (button)
        {
        // left click opens up cell that was clicked on
        case GLUT_LEFT_BUTTON:
            game.open(x / (_w / game.getColumns()), y / (_h / game.getRows()));
            break;
        
        // right click flags the cell that was clicked on
        case GLUT_RIGHT_BUTTON:
            game.flag(x / (_w / game.getColumns()), y / (_h / game.getRows()));
            break;
        }

        // redisplay game board with new updates
        glutPostRedisplay();
    }
}

// keyboard function that determins how a user can interact with the game via keystrokes
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // the Q key will quit the game and close the game window
    case 'Q':
    case 'q':
        exit(0);
        break;

    // the R key will restart the current game without closing the game window
    case 'R':
    case 'r':
        game.Init(); // re-initialise game board
        glutMouseFunc(mouse); // enable mouse interactions with game in the case that it was disabled i.e game over or game win
        glutPostRedisplay(); // redisplay game board with new updates
        break;
    }
}

int main(int argc, char **argv)
{
    // glut initializations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(game.getColumns() * 30, game.getRows() * 30);

    // set the x and y coordinates of the game window to center it on the screen
    // however if screen width or height is not obtainable set the x and y coordinates to 100 pixels and 120 pixels respectively
    int xpos_init = (glutGet(GLUT_SCREEN_WIDTH)) ? (glutGet(GLUT_SCREEN_WIDTH) - glutGet(GLUT_INIT_WINDOW_WIDTH)) / 2 : 100;
    int ypos_init = (glutGet(GLUT_SCREEN_HEIGHT)) ? (glutGet(GLUT_SCREEN_HEIGHT) - glutGet(GLUT_INIT_WINDOW_HEIGHT)) / 2 : 120;
    glutInitWindowPosition(xpos_init, ypos_init);

    glutCreateWindow("Minesweeper");

    // use callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();

    return 0;
}