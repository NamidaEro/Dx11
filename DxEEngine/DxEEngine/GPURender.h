#ifndef CGPURENDER_H__
#define CGPURENDER_H__

#include "Includes.h"
#include "IRender.h"

START(dxengine)

class DXAPI CGPURender : public IRender
{
public:
	CGPURender() {}
	CGPURender(const CGPURender& other) {}
	~CGPURender() {}

public:
	// IRender을(를) 통해 상속됨
	virtual bool Initialize(ID3D11Device* device, HWND hwnd) override;
	virtual void Shutdown() override;
	virtual bool Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture = nullptr) override;

protected:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename) override;
	virtual void ShutdownShader() override;
	virtual void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename) override;
	virtual bool SetShaderParameters(ID3D11DeviceContext* context, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture = nullptr) override;
	virtual void RenderShader(ID3D11DeviceContext* context, int indexCount) override;
};

END

#endif // !CGPURENDER_H__