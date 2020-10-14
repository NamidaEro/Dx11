#ifndef VERTEX_H__
#define VERTEX_H__

#include "Vector3.h"

START(dxengine)

class DXAPI Vertex
{
public:
	Vector3 position;
	Vector4 color;
};

END
#endif // !VERTEX_H__