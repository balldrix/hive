#include "Graphics.h"
#include "Constants.h"
#include "Error.h"
#include "Window.h"

using namespace GlobalConstants;

Graphics::Graphics() :
	m_hWnd(nullptr),
	m_hInstance(nullptr),
	m_swapchain(nullptr),
	m_D3DDevice(nullptr),
	m_D3DDeviceContext(nullptr),
	m_renderTargetView(nullptr),
	m_backbuffer(nullptr),
	m_samplerState(nullptr),
	m_spriteBatch(nullptr),
	m_fullscreen(false),
	m_gameWidth(0.0f),
	m_gameHeight(0.0f),
	m_viewport(D3D11_VIEWPORT())
{
}

Graphics::~Graphics()
{
	if(m_spriteBatch)
	{
		delete m_spriteBatch;
		m_spriteBatch = nullptr;
	}
}

void Graphics::Init(HWND hWnd, HINSTANCE hInstance)
{
	HRESULT result;
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferCount = 2;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = GameWidth;
	scd.BufferDesc.Height = GameHeight;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = m_hWnd;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.Windowed = !m_fullscreen;
	scd.Flags = 0;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	
	static const D3D_FEATURE_LEVEL featureLevels[] =
	{
		// TODO: Modify for supported Direct3D feature levels
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&scd,
		&m_swapchain,
		&m_D3DDevice,
		nullptr,
		&m_D3DDeviceContext);

	// error checking
	if(result != S_OK)
	{
		// log error in txt file
		Error::FileLog("Error Creating D3D11 Device in Graphics.cpp Line 55; \n");

		MessageBox(m_hWnd, L"Graphics Init Error. See Logs/Error.txt", L"Error!", MB_OK); // message

		PostQuitMessage(0); // quit game
	}

	CreateResources(GameWidth, GameHeight);
}

void Graphics::CreateResources(UINT width, UINT height)
{
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	m_D3DDeviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
	m_renderTargetView = nullptr;
	m_D3DDeviceContext->Flush();

	if(m_swapchain != nullptr) { m_swapchain->ResizeBuffers(2, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, 0); }

	// Get backbuffer pointer from swapchain
	HRESULT result = m_swapchain->GetBuffer(0, __uuidof(m_backbuffer), (void**) &m_backbuffer);

	// error checking
	if(result != S_OK)
	{
		// log error in txt file
		Error::FileLog("Error getting Back Buffer in Graphics.cpp Line 76; \n");

		MessageBox(m_hWnd, L"Graphics Init Error. See Logs/Error.txt", L"Error!", MB_OK); // message box

		PostQuitMessage(0); // quit game
	}

	// create render target view
	if(m_backbuffer)
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
	m_viewport.Width = (float) width;
	m_viewport.Height = (float) height;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_D3DDeviceContext->RSSetViewports(1, &m_viewport);

	// create samplerstate description
	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.MaxAnisotropy = (m_D3DDevice->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1)?D3D11_MAX_MAXANISOTROPY:2;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;

	result = m_D3DDevice->CreateSamplerState(&sd, &m_samplerState);

	// error checking
	if(result != S_OK)
	{
		// log error in txt file
		Error::FileLog("Error Creating Sampler State in Graphics Line 128; \n");

		MessageBox(m_hWnd, L"Graphics Init Error. See Logs/Error.txt", L"Error!", MB_OK); // message box

		PostQuitMessage(0); // quit game
	}

	// initialse sprite batch engine
	if(m_D3DDeviceContext)
		m_spriteBatch = new SpriteBatch(m_D3DDeviceContext);

	// set game dimensions
	m_gameWidth = width;
	m_gameHeight = height;
}

void Graphics::ReleaseAll()
{
	if(m_swapchain) { m_swapchain->SetFullscreenState(FALSE, nullptr); }    // switch to windowed mode
	if(m_samplerState) { m_samplerState->Release(); }
	if(m_renderTargetView) { m_renderTargetView->Release(); }
	if(m_D3DDeviceContext) { m_D3DDeviceContext->Release(); }
	if(m_D3DDevice) { m_D3DDevice->Release(); }
	if(m_swapchain) { m_swapchain->Release(); }
}

void Graphics::BeginScene()
{
	// bind render target view and depth stencil view in graphics pipeline
	m_D3DDeviceContext->OMSetRenderTargets(1, &m_renderTargetView, nullptr);

	// clear backbuffer
	m_D3DDeviceContext->ClearRenderTargetView(m_renderTargetView, BackColor);

	// reset Rasterisation state to normal state
	m_D3DDeviceContext->RSSetState(0);

	// reset depth stencil state to normal state
	m_D3DDeviceContext->OMSetDepthStencilState(0, 0);

	// reset viewport
	m_D3DDeviceContext->RSSetViewports(1, &m_viewport);

	// begin sprite scene
	m_spriteBatch->Begin(SpriteSortMode_FrontToBack, nullptr, m_samplerState);
}

void Graphics::PresentBackBuffer()
{
	m_spriteBatch->End();
	m_swapchain->Present(0, 0);
}
