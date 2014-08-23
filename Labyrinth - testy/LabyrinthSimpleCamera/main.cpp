


#include <windows.h>

#include "GL/glu.h"
#include "GL/glut.h"

#include "camera.h"

#include <stdio.h>


bool keys[256] = { false }; // obsluga sterowania
char buffer[256]; // wyswietlane napisy na pasku okienka
Camera _camera;


void drawCube()
{
    glPushMatrix();

    _camera.use();

    glColor3f(0.0, 1.0, 0.0);

    glBegin( GL_LINES );

    glutWireCube(1.0);

    glEnd();

    glPopMatrix();
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0, 0, -5);

    drawCube();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective (60, (GLfloat)width / (GLfloat)height, 0.1, 100.0);

    display();
}

void keyDown(unsigned char key, int width, int height)
{
    keys[key] = true;
}

void keyUp(unsigned char key, int width, int height)
{
    keys[key] = false;
}

void updateCamera()
{
    if(keys['w'])
        _camera.moveForward(1.0);

    if(keys['s'])
        _camera.moveBackward(1.0);

    if(keys['a'])
        _camera.shiftLeft(1.0);

    if(keys['d'])
        _camera.shiftRight(1.0);
}

void idle()
{
    updateCamera();

    Vector3D eye = _camera.getEye();
    Vector3D target = _camera.getTarget();

    sprintf(buffer, "eye=(%f, %f, %f) target=(%f, %f, %f)", eye.x, eye.y, eye.z, target.x, target.y, target.z);
    glutSetWindowTitle(buffer);

    glutPostRedisplay();
    Sleep(10);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Labyrinth");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}

