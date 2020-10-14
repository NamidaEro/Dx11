#include "pch.h"
#include "Vector3.h"

USING(dxengine)

bool Vector3::Equals(const Vector3& rhs)
{
    if (this->x != rhs.x) { return false; }
    if (this->y != rhs.y) { return false; }
    if (this->z != rhs.z) { return false; }
    if (this->w != rhs.w) { return false; }
    return true;
}

Vector3& Vector3::operator=(const Vector3& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;
    this->w = rhs.w;
    return *this;
}

bool Vector3::operator==(const Vector3& rhs)
{
    return Equals(rhs);
}

bool Vector3::operator!=(const Vector3& rhs)
{
    return !Equals(rhs);
}
