// Graphics.h
// Christopher Ball 2019-2021

#pragma once

#include "pch.h"

class Graphics
{
public:
	Graphics();					
	~Graphics();			
	void						Init(HWND hWindow, HINSTANCE hInstance);
	void						CreateResources(UINT width, UINT height);

	void						ReleaseAll();								
	void						BeginScene();								
	
	void						PresentBackBuffer();

	ID3D11Device*				GetDevice() const { return m_D3DDevice; }			
	ID3D11DeviceContext*		GetDeviceContext() const { return m_D3DDeviceContext; }
	IDXGISwapChain*				GetSwapChain() const { return m_swapchain; }

	SpriteBatch*				GetSpriteBatch() const { return m_spriteBatch; }	
	
	float						GetWidth()	const { return m_gameWidth; }			
	float						GetHeight()	const { return m_gameHeight; }			
	
	HWND						GetHwnd()	const { return m_hWnd; }		
	HINSTANCE					GetHInstance() const { return m_hInstance; }
	bool						GetFullscreen() const { return m_fullscreen; }

private:
	HWND						m_hWnd;				
	HINSTANCE					m_hInstance;		
	
	IDXGISwapChain*				m_swapchain;		
	ID3D11Device*				m_D3DDevice;		
	ID3D11DeviceContext*		m_D3DDeviceContext;	

	ID3D11RenderTargetView*		m_renderTargetView;	
	ID3D11Texture2D*			m_backbuffer;		

	ID3D11SamplerState*			m_samplerState;		

	SpriteBatch*				m_spriteBatch;		
	D3D11_VIEWPORT				m_viewport;			

	bool						m_fullscreen;		
	
	float						m_gameWidth;		
	float						m_gameHeight;		
};
