#ifndef CAMERA_H
#define CAMERA_H

#include "vector3d.h"


namespace engine
{
    class Camera
    {
    private:
        double _azimuthalAngle, _polarAngle;

        double _moveSpeed;
        Vector3D _eye, _target;

        void updateTarget();

    public:
        Camera();

		double getAzimuthalAngle();
        void setAzimuthalAngle(double angle);

		double getPolarAngle();
        void setPolarAngle(double angle);

		double getMoveSpeed();
        void setMoveSpeed(double speed);

        void setEye(double x, double y, double z);

        Vector3D getEye();
        Vector3D getTarget();

        void moveForward(double distance);
        void moveBackward(double distance);
        void turnLeft(double angle);
        void turnRight(double angle);

        void shiftLeft(double distance);
        void shiftRight(double distance);

        void use();
    };
}

#endif // CAMERA_H
