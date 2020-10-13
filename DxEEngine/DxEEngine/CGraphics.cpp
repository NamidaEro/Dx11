// Copyright YUI, Inc. All Rights Reserved.
#include "pch.h"
#include "CGraphics.h"

#include "CD3D.h"

USING(dxengine);

CGraphics::CGraphics()
{
	m_pD3D = nullptr;
}

CGraphics::CGraphics(const CGraphics&)
{
	m_pD3D = nullptr;
}

CGraphics::~CGraphics()
{
}

bool CGraphics::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the Direct3D object.
	m_pD3D = new CD3D();
	if (!m_pD3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_pD3D->Initialize(
		hwnd,
		screenWidth, screenHeight,
		SCREEN_DEPTH, SCREEN_NEAR,
		VSYNC_ENABLED, FULL_SCREEN);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void CGraphics::Shutdown()
{
	if(m_pD3D)
	{
		m_pD3D->Shutdown();
		delete m_pD3D;
		m_pD3D = 0;
	}
}

bool CGraphics::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool CGraphics::Render()
{
	// Clear the buffers to begin the scene.
	m_pD3D->BeginScene(0.0f, 0.0f, 1.0f, 1.0f);


	// Present the rendered scene to the screen.
	m_pD3D->EndScene();

	return true;
}
