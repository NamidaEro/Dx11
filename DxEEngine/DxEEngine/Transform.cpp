#include "pch.h"
#include "Transform.h"

USING(dxengine)

Transform::Transform()
	: localPosition(0.0f, 0.0f, 0.0f, 0.0f)
	, localEulerAngles(0.0f, 0.0f, 0.0f, 0.0f)
	, localScale(1.0f, 1.0f, 1.0f, 0.0f)
	, localRotation(0.0f, 0.0f, 0.0f, 0.0f)
	, position(0.0f, 0.0f, 0.0f, 0.0f)
	, eulerAngles(0.0f, 0.0f, 0.0f, 0.0f)
	, scale(1.0f, 1.0f, 1.0f, 0.0f)
	, rotation(0.0f, 0.0f, 0.0f, 0.0f)
{

}
