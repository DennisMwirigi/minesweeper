#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#include "../include/draw.hpp"

Draw draw;

void display()
{
    std::cout << "drawing grid...\n";

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    draw.drawBoard();

    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, draw.COLUMNS * draw.CELL_SIZE, draw.ROWS * draw.CELL_SIZE, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100, 120);
    glutInitWindowSize(draw.COLUMNS * 30, draw.ROWS * 30);

    glutCreateWindow("Minesweeper");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();

    return 0;
}