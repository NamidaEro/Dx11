// Copyright YUI, Inc. All Rights Reserved.
#ifndef CDxManager_h_
#define CDxManager_h_

#include "Includes.h"
START(dxengine)
class CGraphics;
class DXAPI CDxManager
{
public:
	CDxManager();
	~CDxManager();

public:
	bool Initailize(HWND hwnd
		, int screenWidth, int screenHeight
		, float screenDepth, float screenNear
		, bool vsync, bool fullscreen);
	void Shutdown();
	bool Frame();

public:
	void SetCameraPosition(XMFLOAT3& position);

public:
	CGraphics* m_pGraphics = nullptr;
};
END
#endif // !CDxManager_h_
