// Copyright YUI, Inc. All Rights Reserved.

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Includes.h"

START(dxengine)

class CD3D;
class CGraphics : public ISystemObject
{
public:
	CGraphics();
	CGraphics(const CGraphics&);
	~CGraphics();

public:
	bool	Initialize(HWND hwnd, int screenWidth, int screenHeight);
	void	Shutdown();

	bool	Frame();

private:
	bool	Render();

public:
	bool	FULL_SCREEN = false;
	bool	VSYNC_ENABLED = false;
	float	SCREEN_DEPTH = 1000.0f;
	float	SCREEN_NEAR = false;

private:
	CD3D* m_pD3D;
};

END

#endif // !GRAPHICS_H_
