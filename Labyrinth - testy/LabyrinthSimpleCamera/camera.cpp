#include "camera.h"
#include <GL/glu.h>
#include <math.h>

Camera::Camera()
{
    this->_moveSpeed = 0.1;

    this->_eye.x = 0.0;
    this->_eye.y = 0.0;
    this->_eye.z = 0.0;

    this->_target.x = 0.0;
    this->_target.y = 0.0;
    this->_target.z = 0.1;
}


Vector3D Camera::getEye()
{
    return this->_eye;
}

Vector3D Camera::getTarget()
{
    return this->_target;
}

void Camera::moveForward(double distance)
{
    this->_eye.z += distance * this->_moveSpeed;
}

void Camera::moveBackward(double distance)
{
    this->_eye.z -= distance * this->_moveSpeed;
}

void Camera::shiftLeft(double distance)
{
    this->_eye.x += distance * this->_moveSpeed;
}

void Camera::shiftRight(double distance)
{
    this->_eye.x -= distance * this->_moveSpeed;
}

void Camera::use()
{
    double targetX = this->_eye.x ;
    double targetZ = this->_eye.z + 0.0000001;

    ::gluLookAt(this->_eye.x, 0, this->_eye.z, targetX, 0, targetZ, 0.0, 1.0, 0.0);
}
