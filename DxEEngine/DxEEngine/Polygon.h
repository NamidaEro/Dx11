#ifndef POLYGON_H__
#define POLYGON_H__

#include "Includes.h"
#include "Vertex.h"

START(dxengine)

class DXAPI Polygon
{
public:
	virtual bool Initialize(ID3D11Device* device);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext* context);

	int GetIndexCount() { return m_indexCount; }

protected:
	virtual bool InitializeBuffers(ID3D11Device* device);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext* context);

protected:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;

	//Vertex* vertices;
	unsigned long* indices;
};

END

#endif // !POLYGON_H__