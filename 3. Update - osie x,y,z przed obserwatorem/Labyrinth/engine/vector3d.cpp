#include "vector3d.h"

namespace engine
{
    Vector3D::Vector3D()
    {
    }

    Vector3D &Vector3D::operator *=(double value)
    {
        this->x *= value;
        this->y *= value;
        this->z *= value;

        return *this;
    }

    Vector3D &Vector3D::operator +=(Vector3D &vector)
    {
        this->x += vector.x;
        this->y += vector.y;
        this->z += vector.z;

        return *this;
    }
}
