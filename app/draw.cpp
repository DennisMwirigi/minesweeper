#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <string.h>

#include "../include/draw.hpp"

void Draw::drawClosedCell(int x, int y)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f((x * CELL_SIZE), (y * CELL_SIZE));
    glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
    glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
    glEnd();
}

void Draw::drawOpenCell(int x, int y)
{
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f((x * CELL_SIZE), (y * CELL_SIZE));
    glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f((x + 1) * CELL_SIZE - 1, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE - 1);
    glVertex2f((x + 1) * CELL_SIZE - 1, (y + 1) * CELL_SIZE - 1);
    glEnd();
}

void Draw::drawOpenCellNumMines(int x, int y, int minesAdjacent)
{
    drawOpenCell(x, y);
    if (minesAdjacent > 0)
    {
        switch (minesAdjacent)
        {
        case 1:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 2:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case 3:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 4:
            glColor3f(0.0f, 0.7f, 0.0f);
            break;
        case 5:
            glColor3f(0.5f, 0.4f, 0.0f);
            break;
        case 6:
            glColor3f(0.0f, 0.8f, 0.5f);
            break;
        case 7:
            glColor3f(0.1f, 0.1f, 0.1f);
            break;
        case 8:
            glColor3f(0.3f, 0.3f, 0.3f);
            break;
        }
        glRasterPos2f(x * CELL_SIZE + (15 - 5) / 2 + 1, (y + 1) * CELL_SIZE - 5);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + minesAdjacent);
    }
}

void Draw::drawFlag(int x, int y)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, y * CELL_SIZE);
    glVertex2f((x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
    glVertex2f(x * CELL_SIZE, (y + 1) * CELL_SIZE);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + 3);
    glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 - 6, y * CELL_SIZE + 3 + 3);
    glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + 3 + 3 + 3);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + 3);
    glVertex2f(x * CELL_SIZE + CELL_SIZE / 2, (y + 1) * CELL_SIZE - 3);
    glEnd();
}

void Draw::drawMine(int x, int y)
{
    drawOpenCell(x, y);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; ++i)
        glVertex2f(x * CELL_SIZE + CELL_SIZE / 2 + 5.0f * cos(2 * 3.1415926 * i / 5),
                   y * CELL_SIZE + CELL_SIZE / 2 + 5.0f * sin(2 * 3.1415926 * i / 5));
    glEnd();
}

void Draw::gameOver()
{
    glutMouseFunc(NULL);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 3);
    glVertex2f(120, 3);
    glVertex2f(120, 12);
    glVertex2f(0, 12);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    drawText("G  A  M  E    O  V  E  R", 0, 10);
}

void Draw::gameWin()
{
    glutMouseFunc(NULL);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0, 3);
    glVertex2f(105, 3);
    glVertex2f(105, 12);
    glVertex2f(0, 12);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    drawText("Y  O  U    W  I  N  !", 0, 10);
}

void Draw::drawText(const char *text, int x, int y, int z)
{
    glRasterPos3f(x, y, z);
    for (int i = 0; i < strlen(text); i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
}

int Draw::getCellSize()
{
    return CELL_SIZE;
}