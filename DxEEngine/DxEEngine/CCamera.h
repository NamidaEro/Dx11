#ifndef CCAMERA_H__
#define CCAMERA_H__

#include "Includes.h"
#include "CGameObject.h"

START(dxengine)
class CCamera : public CGameObject
{
public:
	CCamera();
	CCamera(const CCamera& other);
	~CCamera();

public:
	void		Render();
	void		GetViewMatrix(XMMATRIX& viewMatrix);

public:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;
};
END

#endif // !CCAMERA_H__



