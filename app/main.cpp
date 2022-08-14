#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "../include/definitions.hpp"
#include "../include/game.hpp"
#include "../include/draw.hpp"

Game game;
Draw draw;

void display()
{
    std::cout << "drawing grid...\n";

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    game.draw();

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game.COLUMNS * CELL_SIZE, game.ROWS * CELL_SIZE, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 120);
    glutInitWindowSize(game.COLUMNS * 30, game.ROWS * 30);

    glutCreateWindow("Minesweeper");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();

    return 0;
}