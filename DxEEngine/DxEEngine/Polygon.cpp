#include "pch.h"
#include "Polygon.h"

#include <d3d11.h>
#include <D3DX10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

USING(dxengine)

bool Polygon::Initialize(ID3D11Device* device)
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
