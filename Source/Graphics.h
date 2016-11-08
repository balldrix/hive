// Graphics.h
// Christopher Ball 2016
// This class manages DirectX and all the functions for 
// drawing to the screen

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "pch.h"

class Graphics
{
public:
	Graphics();					
	~Graphics();			
	void						Init(HWND hWindow, HINSTANCE hInstance);	// initialises graphics device
	void						ReleaseAll();								// release all ID3D11 pointers
	void						BeginScene();								// prepare render target for rendering scene
	
	void						PresentBackBuffer();						// present backbuffer to screen

	ID3D11Device*				GetDevice() { return m_D3DDevice; }			// return graphics device pointer
	ID3D11DeviceContext*		GetDeviceContext() { return m_D3DDeviceContext; }	// return graphics context pointer
	
	SpriteBatch*				GetSpriteBatch() const { return m_spriteBatch; }	// return spritebatch pointer
	
	float GetWidth()	const { return m_gameWidth; }					// return game window width
	float GetHeight()	const { return m_gameHeight; }					// return game window height
	
	HWND GetHwnd()		const { return m_hWnd; }						// return window handle

private:
	HWND						m_hWnd;					// handle to the window
	HINSTANCE					m_hInstance;			// instance of our window
	
	IDXGISwapChain*				m_swapchain;			// pointer to swapchain of frame buffers
	ID3D11Device*				m_D3DDevice;			// pointer to D3D Device
	ID3D11DeviceContext*		m_D3DDeviceContext;		// pointer to D3D Context

	ID3D11RenderTargetView*		m_renderTargetView;		// pointer to render target view
	ID3D11Texture2D*			m_backbuffer;			// pointer to 2d backbuffer

	SpriteBatch*				m_spriteBatch;			// spritebatch for drawing sprites to backbuffer

	bool						m_fullScreen;			// fullscreen setting
	
	float						m_gameWidth;			// client window width
	float						m_gameHeight;			// client window height
};

#endif _GRAPHICS_H_
