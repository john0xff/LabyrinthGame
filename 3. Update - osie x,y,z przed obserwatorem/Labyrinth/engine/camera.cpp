#include "camera.h"

#include <GL/glu.h>
#include <math.h>


namespace engine
{
    //double way = 0.0;

    void Camera::updateTarget()
    {
        double tmp = ::cos(this->_polarAngle);

        this->_target.x = this->_moveSpeed * (tmp * ::cos(this->_azimuthalAngle));
        this->_target.y = this->_moveSpeed * ::sin(this->_polarAngle);
        this->_target.z = this->_moveSpeed * (tmp * ::sin(this->_azimuthalAngle));
    }

    Camera::Camera()
    {
        this->_azimuthalAngle = 1.57075;
        this->_polarAngle = 0.0;

        this->_moveSpeed = 0.1;

        this->_eye.x = 0.0;
        this->_eye.y = 0.0;
        this->_eye.z = 0.0;

		this->updateTarget();
	}

	double Camera::getAzimuthalAngle()
	{
		return 57.2957795457 * this->_azimuthalAngle;
	}

    void Camera::setAzimuthalAngle(double angle)
    {
		this->_azimuthalAngle = 0.01745329251 * angle;
		this->updateTarget();
	}

	double Camera::getPolarAngle()
	{
		return 57.2957795457 * this->_polarAngle;
	}

    void Camera::setPolarAngle(double angle)
    {
        this->_azimuthalAngle = 0.01745329251 * angle;
		this->updateTarget();
	}

	double Camera::getMoveSpeed()
	{
		return this->_moveSpeed;
	}

    void Camera::setMoveSpeed(double speed)
    {
        this->_moveSpeed = speed;
		this->updateTarget();
    }

    void Camera::setEye(double x, double y, double z)
    {
        this->_eye.x = x;
        this->_eye.y = y;
        this->_eye.z = z;
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
        this->_eye.x += distance * this->_target.x;
        this->_eye.y += distance * this->_target.y;
        this->_eye.z += distance * this->_target.z;

        //this->_eye.y += 0.01 * ::sin(way);
        //way += 0.1;
    }

    void Camera::moveBackward(double distance)
    {
        distance = -distance;

        this->_eye.x += distance * this->_target.x;
        this->_eye.y += distance * this->_target.y;
        this->_eye.z += distance * this->_target.z;

        //this->_eye.y += 0.01 * ::sin(way);
        //way -= 0.1;
    }

    void Camera::turnLeft(double angle)
    {
        this->_azimuthalAngle -= 0.01745329251 * angle;
        this->updateTarget();
    }

    void Camera::turnRight(double angle)
    {
        this->_azimuthalAngle += 0.01745329251 * angle;
        this->updateTarget();
    }

    void Camera::shiftLeft(double distance)
    {
        //TODO: zrobic dla 3D

        // tymczsowa wersja
        this->_eye.x += distance * this->_target.z;
        this->_eye.z -= distance * this->_target.x;
    }

    void Camera::shiftRight(double distance)
    {
        //TODO: zrobic dla 3D

        // tymczsowa wersja
        this->_eye.x -= distance * this->_target.z;
        this->_eye.z += distance * this->_target.x;
    }

    void Camera::use()
    {
        double targetX = this->_eye.x + this->_target.x;
        double targetY = this->_eye.y + this->_target.y;
        double targetZ = this->_eye.z + this->_target.z;

        ::gluLookAt(this->_eye.x, this->_eye.y, this->_eye.z, targetX, targetY, targetZ, 0.0, 1.0, 0.0);
    }
}
