// Copyright YUI, Inc. All Rights Reserved.

#include "pch.h"
#include "CDxManager.h"

#include "CGraphics.h"

USING(dxengine)
CDxManager::CDxManager()
{
	if (nullptr == m_pGraphics)
	{
		m_pGraphics = new CGraphics();
	}
}
CDxManager::~CDxManager()
{
	Shutdown();
}
bool CDxManager::Initailize(
	HWND hwnd,
	int screenWidth, int screenHeight,
	float screenDepth, float screenNear,
	bool vsync, bool fullscreen)
{
	m_pGraphics->SCREEN_DEPTH = screenDepth;
	m_pGraphics->SCREEN_NEAR = screenNear;
	m_pGraphics->VSYNC_ENABLED = vsync;
	m_pGraphics->FULL_SCREEN = fullscreen;

	return m_pGraphics->Initialize(hwnd, screenWidth, screenHeight);
}

void CDxManager::Shutdown()
{
	NNULLCHECK_START(m_pGraphics)
		m_pGraphics->Shutdown();
		delete m_pGraphics;
	NNULLCHECK_END
}

bool CDxManager::Frame()
{
	bool result = false;
	NULLCHECK_RET_VALUE(m_pGraphics, false)

	result = m_pGraphics->Frame();

	return result;
}
