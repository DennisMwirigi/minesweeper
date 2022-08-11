#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

int rows, columns = 9;
int cell_height, cell_width = 16;

void drawGrid(int x, int y)
{
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x * rows, y * columns);
    glVertex2f((x + 1) * rows, y * columns);
    glVertex2f((x + 1) * rows, (y + 1) * columns);
    glVertex2f(x * rows, (y + 1) * columns);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(x * cell_width, y * cell_height);
    glVertex2f((x + 1) * cell_width - 1, y * cell_height);
    glVertex2f(x * cell_width, y * cell_height);
    glVertex2f(x * cell_width, (y + 1) * cell_height - 1);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f((x + 1) * cell_width - 1, y * cell_height);
    glVertex2f((x + 1) * cell_width - 1, (y + 1) * cell_height - 1);
    glVertex2f(x * cell_width, (y + 1) * cell_height - 1);
    glVertex2f((x + 1) * cell_width - 1, (y + 1) * cell_height - 1);
    glEnd();

    // std::vector<std::vector<int>> board(rows, std::vector<int>(columns, 0));
    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < columns; j++)
    //     {
    //         std::cout << board[i][j];
    //     }
    //     std::cout << std::endl;
    // }
}

void draw()
{
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < columns; ++x)
        {
            drawGrid(x, y);
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    int width = 640;
    int height = 480;
    glutInitWindowSize(width, height);
    // glutInitWindowSize(columns * cell_width, rows * cell_height);

    // int x = 200;
    // int y = 100;
    glutInitWindowPosition(200, 100);

    glutCreateWindow("Minesweeper");
    // drawGrid(5, 8);

    // GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 1.0f;
    // glClearColor(Red, Green, Blue, Alpha);
    // glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, rows * cell_height, columns * cell_width, 0, -1.0, 1.0);

    glutDisplayFunc(
        []()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            std::cout << "drawing grid...\n";

            glColor3f(0.8f, 0.8f, 0.8f);
            glBegin(GL_QUADS);
            glVertex2f(-0.5, 0.5);
            glVertex2f(0.5, 0.5);
            glVertex2f(0.5, -0.5);
            glVertex2f(-0.5, -0.5);
            glEnd();

            glutSwapBuffers();
        });
    glClearColor(0, 0, 0, 1);
    glutMainLoop();

    // drawGrid(5, 8);

    return 0;
}