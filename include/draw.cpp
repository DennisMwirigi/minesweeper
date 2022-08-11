#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

int rows = 9, columns = 9;
int cell_height = 16, cell_width = 16;

void drawGrid(int x, int y)
{
    glColor3f(0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x * cell_width, y * cell_height);
    glVertex2f((x + 1) * cell_width, y * cell_height);
    glVertex2f((x + 1) * cell_width, (y + 1) * cell_height);
    glVertex2f(x * cell_width, (y + 1) * cell_height);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f((x * cell_width), (y * cell_height));
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

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, rows * cell_height, columns * cell_width, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // glutInitWindowSize(640, 480);
    glutInitWindowSize(columns * cell_width, rows * cell_height);
    glutInitWindowPosition(100, 120);

    glutCreateWindow("Minesweeper");

    glutDisplayFunc(
        []()
        {
            std::cout << "drawing grid...\n";

            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();

            draw();

            glutSwapBuffers();
            glFlush();
        });
    glutReshapeFunc(reshape);

    glClearColor(0, 0, 0, 1);

    glutMainLoop();

    return 0;
}