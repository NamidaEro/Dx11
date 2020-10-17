// Copyright YUI, Inc. All Rights Reserved.
#ifndef D3D_H__
#define D3D_H__
#include "Includes.h"

START(dxengine)

class CD3D : public ISystemObject
{
public:
	CD3D();
	CD3D(const CD3D& other);
	~CD3D();

public:
	bool						Initialize();
	void						Shutdown();

public:
	bool						Initialize(HWND hwnd
								, int screenWidth, int screenHeight
								, float screenDepth, float screenNear
								, bool vsync, bool fullscreen);

public:
	void						BeginScene(float R, float G, float B, float A);
	void						EndScene();

public:
	ID3D11Device*				GetDevice() { return m_device; }
	ID3D11DeviceContext*		GetDeviceContext() { return m_deviceContext; }

public:
	void						GetProjectionMatrix(XMMATRIX& projMatrix) { projMatrix = m_projectionMatrix; }
	void						GetWorldMatrix(XMMATRIX& worldMatrix) { worldMatrix = m_worldMatrix; }
	void						GetOrhoMatrix(XMMATRIX& orthoMatrix) { orthoMatrix = m_orthoMatrix; }

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
	XMMATRIX					m_projectionMatrix;
	XMMATRIX					m_worldMatrix;
	XMMATRIX					m_orthoMatrix;
};

END

#endif // !D3D_H__