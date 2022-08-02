#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    int width = 200;
    int height = 200;
    glutInitWindowSize(width, height);

    int x = 200;
    int y = 100;
    glutInitWindowPosition(x, y);

    int win = glutCreateWindow("Window 1");
    std::cout << "window id: " << win << std::endl;

    GLclampf Red = 1.0f, Green = 0.0f, Blue = 1.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glutDisplayFunc(
        []()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glutSwapBuffers();
        });

    glutMainLoop();

    return 0;
}