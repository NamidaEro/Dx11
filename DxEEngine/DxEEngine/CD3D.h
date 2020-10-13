// Copyright YUI, Inc. All Rights Reserved.
#ifndef D3D_H__
#define D3D_H__

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <D3DX10math.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

START(dxengine)

class CD3D : public Object<CD3D>
{
public:
	CD3D();
	CD3D(const CD3D& other);
	~CD3D();

public:
	// Object을(를) 통해 상속됨
	virtual bool				Initialize() override;
	virtual void				Shutdown() override;

public:
	bool						Initialize(HWND hwnd
								, int screenWidth, int screenHeight
								, float scrennDepth, float screenNear
								, bool vsync, bool fullscreen);

public:
	void						BeginScene(float R, float G, float B, float A);
	void						EndScene();

public:
	ID3D11Device*				GetDevice();
	ID3D11DeviceContext*		GetDeviceContext();

public:
	void						GetProjectionMatrix(D3DXMATRIX& projMatrix);
	void						GetWorkdMatrix(D3DMATRIX& worldMatrix);
	void						GetOrhoMatrix(D3DMATRIX& orthoMatrix);

public:
	void						GetVideoCardInfo(char* cardName, int& memory);

private:
	bool						m_vsync_enabled;
	int							m_videoCardMemory;
	char						m_videoCardDescription[128];
	IDXGISwapChain*				m_swapChain;
	ID3D11Device*				m_device;
	ID3D11DeviceContext*		m_deviceContext;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11Texture2D*			m_depthStencilBuffer;
	ID3D11DepthStencilState*	m_depthStencilState;
	ID3D11DepthStencilView*		m_depthStencilView;
	ID3D11RasterizerState*		m_rasterState;
	D3DXMATRIX					m_projectionMatrix;
	D3DXMATRIX					m_worldMatrix;
	D3DXMATRIX					m_orthoMatrix;
};

END

#endif // !D3D_H__