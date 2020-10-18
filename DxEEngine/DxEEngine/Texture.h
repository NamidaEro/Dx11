#ifndef TEXTURE_H__
#define TEXTURE_H__

#include "Includes.h"

START(dxengine)

class DXAPI Texture
{
private:
	struct TargetHeader
	{
		UCHAR	data1[12];
		UINT16	width;
		UINT16	height;
		UCHAR	bpp;
		UCHAR	data2;
	};

public:
	Texture();
	Texture(const Texture& other);
	~Texture();

public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

protected:
	bool LoadTarga(WCHAR* filename, int& height, int& width);

protected:
	UCHAR* m_targadata = nullptr;
	ID3D11Texture2D* m_texture = nullptr;
	ID3D11ShaderResourceView* m_textureView = nullptr;
};

END

#endif // !TEXTURE_H__
