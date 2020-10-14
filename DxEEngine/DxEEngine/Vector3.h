#ifndef VECTOR3_H__
#define VECTOR3_H__

#include "Includes.h"

START(dxengine)

class DXAPI Vector3
{
public:
	bool Equals(const Vector3& rhs);

public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector3(const float& newX, const float& newY)
		: x(newX), y(newY), z(0.0f), w(0.0f) {}
	Vector3(const float& newX, const float& newY, const float& newZ)
		: x(newX), y(newY), z(newZ), w(0.0f) {}
	Vector3(const float& newX, const float& newY, const float& newZ, const float& newW)
		: x(newX), y(newY), z(newZ), w(newW) {}
	~Vector3() {}

public:
	Vector3& operator=(const Vector3& rhs);
	bool operator==(const Vector3& rhs);
	bool operator!=(const Vector3& rhs);

public:
	float x;
	float y;
	float z;
	float w;
};

typedef Vector3 Vector4;

END

#endif // !VECTOR3_H__



