#ifndef CGPURENDER_H__
#define CGPURENDER_H__

#include "Includes.h"

START(dxengine)

class CGPURender
{
public:
	CGPURender();
	CGPURender(const CGPURender& other);
	~CGPURender();

public:
	bool Initialize(ID3D11Device* device, HWND hwnd);
	void Shutdown();
	bool Render(ID3D11DeviceContext* context, int indexCount
		, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);

private:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

	bool SetShaderParameters(ID3D11DeviceContext* context
		, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
	void RenderShader(ID3D11DeviceContext* context, int indexCount);

private:
	ID3D11VertexShader*		m_vertexShader = nullptr;
	ID3D11PixelShader*		m_pixelShader = nullptr;
	ID3D11InputLayout*		m_layout = nullptr;
	ID3D11Buffer*			m_matrixBuffer = nullptr;
};

END

#endif // !CGPURENDER_H__