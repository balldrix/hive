#include "Graphics.h"
#include "pch.h"

// Constructor
Graphics::Graphics() : 
	m_pD3DDevice	(NULL),
	m_pD3D			(NULL),
	m_hWindow		(NULL),
	m_fullscreen	(false),
	m_width			(0),
	m_height		(0)
{
	m_backColour = Colors::LightGray;
}

// Destructor
Graphics::~Graphics()
{
	ReleaseAll();
}

// initialise directx9 and its parameters
bool
Graphics::Init(HWND hWindow)
{
	// copy window handle
	m_hWindow = hWindow;

	// get screen dimensions from window handle
	RECT rc;
	GetClientRect(m_hWindow, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	// create D3D9 context
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	
	// if context creation fails display error
	if (m_pD3D == NULL)
	{
		MessageBox(m_hWindow, L"Error Intitialising Direct3D!", L"Error!", MB_OK);
		return false;
	}

	// set D3D parameters
	SetD3DPresentParams();

	if (m_fullscreen) // if fullscreen 
	{
		if (IsAdapterCompatable())  // check adapter is compatible
		{
			// set refresh rate with compatible one
			m_pD3DPParams.FullScreen_RefreshRateInHz = m_pMode.RefreshRate;
		}
		else
		{
			// else display error message
			MessageBox(m_hWindow, L"This Graphics device does not support the specified resolution and/or format!", L"Error!", MB_OK);
			return false;
		}
	}

	DWORD fBehaviour;
	D3DCAPS9 caps;

	m_result = m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if ((caps.DevCaps &D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
	{
		fBehaviour = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	else
	{
		fBehaviour = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

	m_result = m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWindow,
		fBehaviour,
		&m_pD3DPParams,
		&m_pD3DDevice);

	if(m_result != D3D_OK)
	{
		MessageBox(m_hWindow, L"Error Creating Direct3D Device!", L"Error!", MB_OK);
		return false;
	}

	m_result = D3DXCreateSprite(m_pD3DDevice, &m_pSprite);

	if(m_result != S_OK)
	{
		std::wstring s = L"Error Creating Sprite!";// +fileName;
		MessageBox(m_hWindow, s.c_str(), L"Error!", MB_OK);
		return false;
	}

	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return true;
}

bool
Graphics::SetD3DPresentParams()
{
	try
	{
		ZeroMemory(&m_pD3DPParams, sizeof(m_pD3DPParams));

		D3DFORMAT BackBufferFMT;
		if (m_fullscreen)
		{
			BackBufferFMT = D3DFMT_X8R8G8B8;
		}
		else
		{
			BackBufferFMT = D3DFMT_UNKNOWN;
		}

		m_pD3DPParams.BackBufferWidth = m_width;
		m_pD3DPParams.BackBufferHeight = m_height;
		m_pD3DPParams.BackBufferFormat = BackBufferFMT;
		m_pD3DPParams.BackBufferCount = 1;
		m_pD3DPParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_pD3DPParams.hDeviceWindow = m_hWindow;
		m_pD3DPParams.Windowed = (!m_fullscreen);
		m_pD3DPParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(TEXT("Error initialising Direct3D presentation parameters"));
		return false;
	}
	return true;
}


bool
Graphics::IsAdapterCompatable()
{
	UINT nModes = m_pD3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, m_pD3DPParams.BackBufferFormat);

	for (UINT index = 0; index < nModes; index++)
	{
		m_result = m_pD3D->EnumAdapterModes(D3DADAPTER_DEFAULT, m_pD3DPParams.BackBufferFormat, index, &m_pMode);
	
		if (m_pMode.Height == m_pD3DPParams.BackBufferHeight &&
			m_pMode.Width == m_pD3DPParams.BackBufferWidth  &&
			m_pMode.RefreshRate >= m_pD3DPParams.FullScreen_RefreshRateInHz)
		
			return true;
	}
	
	return false;
}

// release all graphics pointers
void
Graphics::ReleaseAll()
{
	if(m_pSprite != NULL)
	{
		m_pSprite->Release();
	}

	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
	}

	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
	}
}

// present back buffer
void
Graphics::PresentBackBuffer()
{
	m_result = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	

	if (m_result != D3D_OK)
	{
		MessageBox(m_hWindow, L"Error Presenting Backbuffer!", L"Error!", MB_OK);
		return;
	}
}

// check state of device
HRESULT
Graphics::GetDeviceState()
{
	m_result = E_FAIL;

	if (m_pD3DDevice == NULL)
	{
		return m_result;
	}
	
	m_result = m_pD3DDevice->TestCooperativeLevel();
	
	return m_result;
}

// reset device
HRESULT
Graphics::Reset()
{
	m_result = E_FAIL;
	
	SetD3DPresentParams();
	
	m_result = m_pD3DDevice->Reset(&m_pD3DPParams);
	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	return m_result;
}

void
Graphics::ChangeDisplayMode(DisplayMode mode)
{
	switch (mode)
	{
		case FULLSCREEN:
		{
			if (m_fullscreen)
			{
				return;
			}
			m_fullscreen = true;
			break;
		}
		case WINDOW:
		{
			if (m_fullscreen == false)
			{
				return;
			}
			m_fullscreen = false;
			break;
		}
		default:
			m_fullscreen = !m_fullscreen;
			break;
	}

	Reset();

	if (m_fullscreen)  // fullscreen
	{
		SetWindowLong(m_hWindow, GWL_STYLE, WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP);
	}
	else            // windowed
	{
		SetWindowLong(m_hWindow, GWL_STYLE, WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU);
		SetWindowPos(m_hWindow, HWND_TOP, 0, 0, m_width, m_height,
			SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		// Adjust window size so client area is GAME_WIDTH x GAME_HEIGHT
		RECT clientRect;
		GetClientRect(m_hWindow, &clientRect);   // get size of client area of window
		MoveWindow(m_hWindow,
			0,                                           // Left
			0,                                           // Top
			m_width + (m_width - clientRect.right),    // Right
			m_height + (m_height - clientRect.bottom), // Bottom
			TRUE);                                       // Repaint the window
	}

}

void
Graphics::CreateVertexBuffer(CustomVertex vertex[], UINT size, LPDIRECT3DVERTEXBUFFER9 &vertexBuffer)
{
	m_pD3DDevice->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, CUSTOMFVF, D3DPOOL_DEFAULT, &vertexBuffer, NULL);
	
	void *ptr;
	// lock buffer
	vertexBuffer->Lock(0, size, (void**)&ptr, 0);
	memcpy(ptr, vertex, size);
	vertexBuffer->Unlock();
}

void
Graphics::RenderQuad(LPDIRECT3DVERTEXBUFFER9 vertexBuffer)
{
	HRESULT result = E_FAIL;
	if(vertexBuffer != NULL)
	{
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		m_pD3DDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(CustomVertex));
		m_pD3DDevice->SetFVF(CUSTOMFVF);
		result = m_pD3DDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, 4);
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	if(m_result != D3D_OK)
	{
		MessageBox(m_hWindow, L"Error Drawing Quad!", L"Error!", MB_OK);
		return;
	}
}

void
Graphics::RenderSprite(const SpriteData &spriteData, Color colour)
{
	if(spriteData.texture == NULL)
	{
		return;
	}

	// calculate centre of the sprite
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(spriteData.width / 2 * spriteData.scale),
										   (float)(spriteData.height / 2 * spriteData.scale));

	// Screen position of the sprite
	D3DXVECTOR2 translate = D3DXVECTOR2(spriteData.position.x, spriteData.position.y);

	// Scaling X,Y
	D3DXVECTOR2 scaling(spriteData.scale, spriteData.scale);

	if(spriteData.flipHorizontal)  // if flip horizontal
	{
		scaling.x *= -1;            // negative X scale to flip

									// Get center of flipped image.
		spriteCenter.x -= (float)(spriteData.width * spriteData.scale);

		// Flip occurs around left edge, translate right to put
		// Flipped image in same location as original.
		translate.x += (float)(spriteData.width * spriteData.scale);
	}

	if(spriteData.flipVertical)    // if flip vertical
	{
		scaling.y *= -1;            // negative Y scale to flip

									// Get center of flipped image
		spriteCenter.y -= (float)(spriteData.height * spriteData.scale);

		// Flip occurs around top edge, translate down to put
		// Flipped image in same location as original.
		translate.y += (float)(spriteData.height * spriteData.scale);
	}

	D3DXMATRIX matrix;

	D3DXMatrixTransformation2D(
		&matrix,                // the matrix
		NULL,                   // keep origin at top left when scaling
		0.0f,                   // no scaling rotation
		&scaling,               // scale amount
		&spriteCenter,          // rotation center
		(float)(spriteData.angle),  // rotation angle
		&translate);            // X,Y location

								// Tell the sprite about the new transform matrix
	m_pSprite->SetTransform(&matrix);

	m_pSprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, colour.BGRA());
}

// begin frame
HRESULT
Graphics::BeginScene()
{
	m_result = E_FAIL;
	if(m_pD3DDevice == NULL)
	{
		return m_result;
	}

	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_backColour.BGRA(), 1.0f, 0);

	m_result = m_pD3DDevice->BeginScene();

	return m_result;
}

void 
Graphics::SpriteBegin()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

// end frame
HRESULT
Graphics::EndScene()
{
	m_result = E_FAIL;

	if(m_pD3DDevice == NULL)
	{
		return m_result;
	}
	
	m_result = m_pD3DDevice->EndScene();
}

void 
Graphics::SpriteEnd()
{
	m_pSprite->EndScene();
}
