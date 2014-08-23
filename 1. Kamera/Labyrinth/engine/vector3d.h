#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace engine
{
    class Vector3D
    {
    public:
        double x, y, z;

    public:
        Vector3D();

        Vector3D &operator *= (double value);
        Vector3D &operator += (Vector3D &vector);
    };
}

#endif // VECTOR3D_H
