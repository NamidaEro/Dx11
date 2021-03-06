#ifndef TRIANGLE_H__
#define TRIANGLE_H__

#include "Polygon.h"

START(dxengine)

class DXAPI Triangle : public Polygon
{
public:
	virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext* context);

protected:
	virtual bool InitializeBuffers(ID3D11Device* device);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext* context);
	virtual bool LoadTexture(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename);
	virtual void ReleaseTexture();

public:
	Triangle();
	~Triangle();
};

END

#endif // !TRIANGLE_H__