#include <windows.h>

#include "GL/glu.h"
#include "GL/glut.h"

#include "engine/camera.h"
#include "engine/map.h"

#include <stdio.h>



bool keys[256] = { false };

engine::Camera camera;
engine::Map map;


void drawAxises()
{
	glDisable(GL_DEPTH_TEST);

	glPushMatrix();
	{
		engine::Vector3D eye = camera.getEye();
		engine::Vector3D target = camera.getTarget();

		double moveSpeed = camera.getMoveSpeed();

		double x = eye.x + 3.0 * (target.x / moveSpeed);
		double y = eye.y + 3.0 * (target.y / moveSpeed) - 1.0;
		double z = eye.z + 3.0 * (target.z / moveSpeed);

		glTranslated(x, y, z);
		glLineWidth(2.0f);

		glBegin(GL_LINES);

		// X

		glColor3f(1.0, 0.0, 0.0);

		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		glVertex3f(0.9, 0.0, 0.1);
		glVertex3f(1.1, 0.0, 0.3);
		glVertex3f(1.1, 0.0, 0.1);
		glVertex3f(0.9, 0.0, 0.3);

		// Y

		glColor3f(0.0, 1.0, 0.0);

		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);

		glVertex3f(0.0, 1.15, 0.0);
		glVertex3f(0.0, 1.3, 0.0);

		glVertex3f(0.0, 1.3, 0.0);
		glVertex3f(0.1, 1.5, 0.0);

		glVertex3f(0.0, 1.3, 0.0);
		glVertex3f(-0.1, 1.5, 0.0);

		// Z

		glColor3f(0.0, 0.0, 1.0);

		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);

		glVertex3f(0.1, 0.0, 0.9);
		glVertex3f(0.1, 0.0, 1.1);

		glVertex3f(0.3, 0.0, 0.9);
		glVertex3f(0.3, 0.0, 1.1);

		glVertex3f(0.1, 0.0, 0.9);
		glVertex3f(0.3, 0.0, 1.1);

		glEnd();
	}
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

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
	{
		camera.use();
		map.use();

		drawAxises();
	}
    glPopMatrix();

	glFlush();
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
		camera.moveForward(1.0);

    if(keys['s'])
		camera.moveBackward(1.0);

    if(keys['a'])
		camera.turnLeft(1.0);

    if(keys['d'])
		camera.turnRight(1.0);

    if(keys[','])
		camera.shiftLeft(1.0);

    if(keys['.'])
		camera.shiftRight(1.0);
}

char buffer[256];

void showCameraInformations()
{
	engine::Vector3D eye = camera.getEye();
	engine::Vector3D target = camera.getTarget();

	sprintf(buffer, "eye=(%f, %f, %f) target=(%f, %f, %f)", eye.x, eye.y, eye.z, target.x, target.y, target.z);
	glutSetWindowTitle(buffer);
}

void idle()
{
	updateCamera();
	showCameraInformations();

	glutPostRedisplay();
	glutSwapBuffers();

	Sleep(10);
}

int main(int argc, char** argv)
{
	if(map.load("mapa.txt") == false)
		return 1;

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT);

    glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if(map.create() == false)
		return 2;

	camera.setEye(6.0, 1.5, 6.0);
	camera.setMoveSpeed(0.1);

    glutMainLoop();

    return 0;
}
