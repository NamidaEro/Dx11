#include "pch.h"
#include "CCamera.h"

#include <d3dx10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

USING(dxengine)

CCamera::CCamera()
    : m_viewMatrix(new D3DXMATRIX)
{
}

CCamera::CCamera(const CCamera& other)
    : m_viewMatrix(other.m_viewMatrix)
{
}

CCamera::~CCamera()
{
    delete m_viewMatrix;
}

void CCamera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = transform.GetlocalPosition().x;
	position.y = transform.GetlocalPosition().y;
	position.z = transform.GetlocalPosition().z;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = transform.GetlocalRotation().x * 0.0174532925f;
	yaw = transform.GetlocalRotation().y * 0.0174532925f;
	roll = transform.GetlocalRotation().z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(m_viewMatrix, &position, &lookAt, &up);
}

const D3DXMATRIX* CCamera::GetViewMatrix()
{
	return m_viewMatrix;
}
