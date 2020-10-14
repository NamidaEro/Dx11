#ifndef POLYGON_H__
#define POLYGON_H__

#include "Includes.h"
#include "Vertex.h"

class ID3D11Device;
class ID3D11DeviceContext;
class ID3D11Buffer;

START(dxengine)

class DXAPI Polygon
{
public:
	virtual bool Initialize(ID3D11Device* device);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext* context);

protected:
	virtual bool InitializeBuffers(ID3D11Device* device);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext* context);

protected:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
};

END

#endif // !POLYGON_H__