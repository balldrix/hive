#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define WIN32_LEAN_AND_MEAN

#include "pch.h"


enum DisplayMode
{
	TOGGLE,
	FULLSCREEN,
	WINDOW
};

// structure to store properties of a sprite
struct SpriteData
{
	int					width;
	int					height;
	Vector2				position;
	float				scale;
	float				angle;
	RECT				rect;
	LPDIRECT3DTEXTURE9	texture;
	bool				flipHorizontal;
	bool				flipVertical;
};

// structure for drawing primitives using vertexes
struct CustomVertex
{
	float x;
	float y;
	float z;
	float rhw;
	DWORD colour;
};
// set vertex definition 
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

// graphics class to manage directx9 wrapper
class Graphics
{
public:
	// Constructor
	Graphics();
	// Destructor
	~Graphics();

	// initialise directx9 device
	bool				Init(HWND hWindow);

	//check if adapter is compatible with dimensions and refresh rate
	bool				IsAdapterCompatable();

	// release all graphics pointers
	void				ReleaseAll();

	// get D3D device
	LPDIRECT3DDEVICE9	GetD3DDevice()	{ return m_pD3DDevice; }

	// get D3D context
	LPDIRECT3D9			GetD3D()		{ return m_pD3D; }

	// get sprite batch
	LPD3DXSPRITE		GetSprite() const { return m_pSprite; }

	// get handle to my window
	HWND				GetHwnd()		{ return m_hWindow; }

	// check if device is lost
	HRESULT				GetDeviceState();

	// return fullscreen
	bool				GetFullscreen() { return m_fullscreen; }
	
	// reset graphics device
	HRESULT				Reset();

	// set to different display mode
	void				ChangeDisplayMode(DisplayMode mode);

	// begin scene
	HRESULT				BeginScene();
	
	// present back buffer
	void				PresentBackBuffer();

	// end scene
	HRESULT				EndScene();

private:

	// initialise D3D presentation parameters
	bool				SetD3DPresentParams();

	// pointer to D3D device
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	
	// pointer to D3D context
	LPDIRECT3D9				m_pD3D;

	// pointer to D3D parameters
	D3DPRESENT_PARAMETERS	m_pD3DPParams;

	// pointer to DX sprite
	LPD3DXSPRITE			m_pSprite;

	// pointer to screen modes
	D3DDISPLAYMODE			m_pMode;

	// window handle
	HWND					m_hWindow;

	// is game fullscreen
	bool					m_fullscreen;

	//	game width
	int						m_width;
	
	// game height
	int						m_height;

	// winapi result return code
	HRESULT					m_result;

	// colour for backbuffer
	Color				m_backColour;

};

#endif _GRAPHICS_H_