#ifndef QUATERNION_H__
#define QUATERNION_H__

#include "Includes.h"

class DXAPI Quaternion
{
public:
	Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Quaternion(const float& newX, const float& newY, const float& newZ, const float& newW)
		: x(newX), y(newY), z(newZ), w(newW) {}
public:
	float x;
	float y;
	float z;
	float w;
};

#endif // !QUATERNION_H__


