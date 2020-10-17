// Copyright YUI, Inc. All Rights Reserved.
#include "pch.h"
#include "CGraphics.h"

#include "CD3D.h"
#include "CCamera.h"
#include "GPURender.h"
#include "Triangle.h"

#include "ModelClass.h";
#include "ColorShaderClass.h"

USING(dxengine);

CGraphics::CGraphics()
	: m_pD3D(nullptr)
	, m_Camera(nullptr)
	, m_Model(nullptr)
	, m_GPURender(nullptr)
{
	int a = 0;
}

CGraphics::CGraphics(const CGraphics&)
{
}

CGraphics::~CGraphics()
{
	Shutdown();
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

	// Create the camera object.
	m_Camera = new CCamera;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->transform.SetlocalPosition(Vector3(0.0f, 0.0f, -10.0f));
	m_Camera->m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// Create the model object.
	m_Model = new Triangle;
	//m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_pD3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_GPURender = new CGPURender;
	//m_GPURender = new ColorShaderClass;
	if (!m_GPURender)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_GPURender->Initialize(m_pD3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void CGraphics::Shutdown()
{
	// Release the color shader object.
	if (m_GPURender)
	{
		m_GPURender->Shutdown();
		delete m_GPURender;
		m_GPURender = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

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
	XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_pD3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_pD3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_pD3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_pD3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_GPURender->Render(m_pD3D->GetDeviceContext()
		, m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}


	// Present the rendered scene to the screen.
	m_pD3D->EndScene();

	return true;
}

void CGraphics::SetCameraPosition(XMFLOAT3& position)
{
	m_Camera->m_position = position;
}
