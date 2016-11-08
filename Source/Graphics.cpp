#include "Graphics.h"
#include "Constants.h"
#include "Error.h"

Graphics::Graphics() :
m_hWnd(nullptr),
m_hInstance(nullptr),			
m_swapchain(nullptr),
m_D3DDevice(nullptr),
m_D3DDeviceContext(nullptr),
m_renderTargetView(nullptr),
m_backbuffer(nullptr),
m_spriteBatch(nullptr),
m_fullScreen(false),
m_gameWidth(0.0f),
m_gameHeight(0.0f)
{
}

Graphics::~Graphics()
{
	// delete 2d sprite batch engine
	if(m_spriteBatch)
	{
		delete m_spriteBatch;
		m_spriteBatch = nullptr;
	}
}

void
Graphics::Init(HWND hWnd, HINSTANCE hInstance)
{
	HRESULT result; // used for error checking
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	// get screen dimensions from window handle
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	// Initialise DirectX
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = m_hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = !m_fullScreen;
	result = D3D11CreateDeviceAndSwapChain(NULL,
								  D3D_DRIVER_TYPE_HARDWARE,
								  NULL,
								  NULL,
								  NULL,
								  NULL,
								  D3D11_SDK_VERSION,
								  &scd,
								  &m_swapchain,
								  &m_D3DDevice,
								  NULL,
								  &m_D3DDeviceContext);

	// error checking
	if(result != S_OK)
	{
		// log error in txt file
		Error::FileLog("Error Creating D3D11 Device in Graphics.cpp Line 55; \n");
		
		MessageBox(m_hWnd, L"Graphics Init Error. See Logs/Error.txt", L"Error!", MB_OK); // message
	
		PostQuitMessage(0); // quit game
	}

	// Get backbuffer pointer from swapchain
	result = m_swapchain->GetBuffer(0, __uuidof(m_backbuffer), (void**)&m_backbuffer);
	
	// error checking
	if(result != S_OK)
	{
		// log error in txt file
		Error::FileLog("Error getting Back Buffer in Graphics.cpp Line 76; \n");

		MessageBox(m_hWnd, L"Graphics Init Error. See Logs/Error.txt", L"Error!", MB_OK); // message box

		PostQuitMessage(0); // quit game
	}

	// create render target view
	result = m_D3DDevice->CreateRenderTargetView(m_backbuffer, nullptr, &m_renderTargetView);

	// error checking
	if(result != S_OK)
	{
		// log error in txt file
		Error::FileLog("Error Creating Render Target in Graphics Line 86; \n");

		MessageBox(m_hWnd, L"Graphics Init Error. See Logs/Error.txt", L"Error!", MB_OK); // message box

		PostQuitMessage(0); // quit game
	}

	m_backbuffer->Release();

	// initialise viewport
	D3D11_VIEWPORT vp;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_D3DDeviceContext->RSSetViewports(1, &vp);

	// initialse sprite batch engine
	m_spriteBatch = new SpriteBatch(m_D3DDeviceContext);

	// set game dimensions
	m_gameWidth = (float)width;
	m_gameHeight = (float)height;
}

void Graphics::ReleaseAll()
{
	if(m_renderTargetView) { m_renderTargetView->Release(); }
	if(m_D3DDeviceContext) { m_D3DDeviceContext->Release(); }
	if(m_D3DDevice) { m_D3DDevice->Release(); }
	if(m_swapchain) { m_swapchain->Release(); }
}

void
Graphics::BeginScene()
{
	// bind render target view and depth stencil view in graphics pipeline
	m_D3DDeviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);

	// clear backbuffer
	m_D3DDeviceContext->ClearRenderTargetView(m_renderTargetView, GlobalConstants::BACK_COLOUR);

	// reset Rasterisation state to normal state
	m_D3DDeviceContext->RSSetState(0);

	// reset depth stencil state to normal state
	m_D3DDeviceContext->OMSetDepthStencilState(0, 0);

	// begin sprite scene
	m_spriteBatch->Begin();
}

void
Graphics::PresentBackBuffer()
{
	// end sprite batch rendering
	m_spriteBatch->End();

	// present backbuffer
	m_swapchain->Present(0, 0);
}