#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define WIN32_LEAN_AND_MEAN

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Vector2D.h"
#include "Colours.h"

//#include <stdio.h>
//#include <time.h>
//#include "Constants.h"

namespace graphicsNS
{
	enum DISPLAY_MODE
	{
		TOGGLE,
		FULLSCREEN,
		WINDOW
	};
}

// structure to store properties of a sprite
struct SpriteData
{
	int					width;
	int					height;
	Vector2D			position;
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
	bool				Init(HWND hwnd, int width, int height, bool fullscreen);

	//check if adapter is compatible with dimensions and refresh rate
	bool				IsAdapterCompatable();

	// release all graphics pointers
	void				ReleaseAll();

	// present back buffer
	void				PresentBackBuffer();

	// get D3D device
	LPDIRECT3DDEVICE9	GetD3DDevice()	{ return m_pD3DDevice; }

	// get D3D context
	LPDIRECT3D9			GetD3D()		{ return m_pD3D; }

	// get handle to my window
	HWND				GetHwnd()		{ return m_hWindow; }

	// check if device is lost
	HRESULT				GetDeviceState();

	// return fullscreen
	bool				GetFullscreen() { return m_fullscreen; }
	
	// reset graphics device
	HRESULT				Reset();

	// set to different display mode
	void				ChangeDisplayMode(graphicsNS::DISPLAY_MODE mode);

	// loads texture from file and writes to dx texture
	HRESULT				LoadTexture(const char* filename, LPDIRECT3DTEXTURE9 &texture, D3DCOLOR transKey, UINT &width, UINT &height);

	// create vertex buffer
	void				CreateVertexBuffer(CustomVertex vertex[], UINT size, LPDIRECT3DVERTEXBUFFER9 &vertexBuffer);

	// draw quad using vertex buffer
	void				RenderQuad(LPDIRECT3DVERTEXBUFFER9 vertexBuffer);

	// draw sprite
	void				RenderSprite(const SpriteData &spriteData, D3DCOLOR colour = colourNS::WHITE);

	// begin scene
	HRESULT				Begin();

	// begin sprite drawing
	void				SpriteBegin();

	// end scene
	HRESULT				End();

	// end sprite drawing
	void				SpriteEnd();

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
	D3DCOLOR				m_backColour;

};

#endif _GRAPHICS_H_