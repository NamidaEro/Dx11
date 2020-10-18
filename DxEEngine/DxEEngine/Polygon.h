#ifndef POLYGON_H__
#define POLYGON_H__

#include "Includes.h"
#include "Vertex.h"
#include "Texture.h"

START(dxengine)

class DXAPI Polygon
{
public:
	virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext* context);

	int GetIndexCount() { return m_indexCount; }
	ID3D11ShaderResourceView* GetTexture() { return m_Texture->GetTexture(); }

protected:
	virtual bool InitializeBuffers(ID3D11Device* device);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext* context);
	virtual bool LoadTexture(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename);
	virtual void ReleaseTexture();

protected:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;

	//Vertex* vertices;
	unsigned long* indices;

	Texture* m_Texture = nullptr;
};

END

#endif // !POLYGON_H__