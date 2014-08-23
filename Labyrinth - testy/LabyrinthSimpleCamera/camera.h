


struct Vector3D
{
    double x, y, z;
};

class Camera
{
private:
    double _azimuthalAngle, _polarAngle;

    double _moveSpeed;
    Vector3D _eye, _target;


public:
    Camera();

    Vector3D getEye();
    Vector3D getTarget();

    void moveForward(double distance);
    void moveBackward(double distance);

    void shiftLeft(double distance);
    void shiftRight(double distance);

    void use();
};
