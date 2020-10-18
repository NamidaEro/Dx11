#ifndef IRENDER_H__
#define IRENDER_H__

#include "Includes.h"

START(dxengine)

class DXAPI IRender
{
protected:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};
public:
	IRender() : m_vertexShader(nullptr)	, m_pixelShader(nullptr)
		, m_layout(nullptr), m_matrixBuffer(nullptr) {}
	IRender(const IRender& other) {}
	~IRender() {}

public:
	virtual bool Initialize(ID3D11Device* device, HWND hwnd) = 0;
	virtual void Shutdown() = 0;
	virtual bool Render(ID3D11DeviceContext* context, int indexCount
		, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix
		, ID3D11ShaderResourceView* texture = nullptr) = 0;

protected:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename) = 0;
	virtual void ShutdownShader();
	virtual void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);
	virtual bool SetShaderParameters(ID3D11DeviceContext* context
		, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix
		, ID3D11ShaderResourceView* texture = nullptr) = 0;
	virtual void RenderShader(ID3D11DeviceContext* context, int indexCount);

protected:
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_layout = nullptr;
	ID3D11Buffer* m_matrixBuffer = nullptr;
	ID3D11SamplerState* m_sampleState = nullptr;
};

END

#endif // !IRENDER_H__



