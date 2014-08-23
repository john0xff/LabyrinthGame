#include <windows.h>

#include "GL/glu.h"
#include "GL/glut.h"

#include "engine/camera.h"
#include "engine/map.h"

#include <stdio.h>



bool keys[256] = { false };
engine::Camera _camera;

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (60, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();


    _camera.use();


    glColor3f(0.0, 1.0, 0.0);

    glTranslated(0, 0, 15);


        glBegin( GL_LINES );

         glVertex3f( 1.0, 1.0, 1.0 );
        glVertex3f( 1.0, - 1.0, 1.0 );

        glVertex3f( 1.0, - 1.0, 1.0 );
        glVertex3f( 1.0, - 1.0, - 1.0 );

        glVertex3f( 1.0, - 1.0, - 1.0 );
        glVertex3f( 1.0, 1.0, - 1.0 );

        glVertex3f( 1.0, 1.0, - 1.0 );
        glVertex3f( 1.0, 1.0, 1.0 );

        glVertex3f( - 1.0, 1.0, 1.0 );
        glVertex3f( - 1.0, - 1.0, 1.0 );

        glVertex3f( - 1.0, - 1.0, 1.0 );
        glVertex3f( - 1.0, - 1.0, - 1.0 );

        glVertex3f( - 1.0, - 1.0, - 1.0 );
        glVertex3f( - 1.0, 1.0, - 1.0 );

        glVertex3f( - 1.0, 1.0, - 1.0 );
        glVertex3f( - 1.0, 1.0, 1.0 );

        glVertex3f( 1.0, 1.0, 1.0 );
        glVertex3f( - 1.0, 1.0, 1.0 );

        glVertex3f( 1.0, - 1.0, 1.0 );
        glVertex3f( - 1.0, - 1.0, 1.0 );

        glVertex3f( 1.0, - 1.0, - 1.0 );
        glVertex3f( - 1.0, - 1.0, - 1.0 );

        glVertex3f( 1.0, 1.0, - 1.0 );
        glVertex3f( - 1.0, 1.0, - 1.0 );

        glEnd();



    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y)
{
    keys[key] = true;
}

void keyUp(unsigned char key, int x, int y)
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
        _camera.turnLeft(1.0);

    if(keys['d'])
        _camera.turnRight(1.0);

    if(keys[','])
        _camera.shiftLeft(1.0);

    if(keys['.'])
        _camera.shiftRight(1.0);
}

char buffer[256];

void idle()
{
    updateCamera();

    engine::Vector3D eye = _camera.getEye();
    engine::Vector3D target = _camera.getTarget();

    sprintf(buffer, "eye=(%f, %f, %f) target=(%f, %f, %f)", eye.x, eye.y, eye.z, target.x, target.y, target.z);
    glutSetWindowTitle(buffer);

    glutPostRedisplay();
    Sleep(10);

    //glutGet()
}

int main(int argc, char** argv)
{
    engine::Map map;

    map.load("mapa.txt");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Labyrinth");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
