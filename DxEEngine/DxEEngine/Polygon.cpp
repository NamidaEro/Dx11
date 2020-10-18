#include "pch.h"
#include "Polygon.h"

USING(dxengine)

bool Polygon::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename)
{
	return true;
}

void Polygon::Shutdown()
{
}

void Polygon::Render(ID3D11DeviceContext* context)
{
}

bool Polygon::InitializeBuffers(ID3D11Device* device)
{
	return true;
}

void Polygon::ShutdownBuffers()
{
}

void Polygon::RenderBuffers(ID3D11DeviceContext* context)
{
}

bool Polygon::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename)
{
	return false;
}

void Polygon::ReleaseTexture()
{
}
