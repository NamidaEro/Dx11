#ifndef CCAMERA_H__
#define CCAMERA_H__

#include "Includes.h"
#include "CGameObject.h"

struct D3DXVECTOR3;
struct D3DXMATRIX;

START(dxengine)
class CCamera : public CGameObject
{
public:
	CCamera();
	CCamera(const CCamera& other);
	~CCamera();

public:
};
END

#endif // !CCAMERA_H__



