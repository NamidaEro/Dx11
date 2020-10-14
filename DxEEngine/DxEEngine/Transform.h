#ifndef TRANSFORM_H__
#define TRANSFORM_H__

#include "Includes.h"
#include "Component.h"

START(dxengine)
class DXAPI Transform : public Component
{
	DEF_REF_GS(Vector3, localPosition)
	DEF_REF_GS(Vector3, localEulerAngles)
	DEF_REF_GS(Vector3, localScale)
	DEF_REF_GS(Quaternion, rocalRotation)

	DEF_REF_GS(Vector3, position)
	DEF_REF_GS(Vector3, eulerAngles)
	DEF_REF_GS(Vector3, scale)
	DEF_REF_GS(Quaternion, rotation)
};

END

#endif // !TRANSFORM_H__