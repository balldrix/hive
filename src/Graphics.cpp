#include "Graphics.h"

#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "Logger.h"

using namespace GlobalConstants;
using namespace DirectX;

using Microsoft::WRL::ComPtr;

Graphics::Graphics() :
	m_window(nullptr),
	m_hInstance(nullptr),
	m_featureLevel(D3D_FEATURE_LEVEL_9_1),
	m_fullscreen(false),
	m_backBufferWidth(GameWidth),
	m_backbufferHeight(GameHeight)
{
}

Graphics::~Graphics() { }

void Graphics::Init(HWND hWnd, HINSTANCE hInstance)
{
	m_window = hWnd;
	CreateDevice();
	CreateResources();

	Logger::LogInfo("Initialised Graphics.");
}

void Graphics::CreateDevice()
{
	UINT creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

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

	// Create the DX11 API device object, and get a corresponding context.
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	DX::ThrowIfFailed(D3D11CreateDevice(
		nullptr,                            // specify nullptr to use the default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
		&m_featureLevel,                    // returns feature level of device created
		context.ReleaseAndGetAddressOf()    // returns the device immediate context
	));

#ifndef DEBUG
	ComPtr<ID3D11Debug> d3dDebug;
	if(SUCCEEDED(device.As(&d3dDebug)))
	{
		ComPtr<ID3D11InfoQueue> d3dInfoQueue;
		if(SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
		{
#ifdef _DEBUG
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
			d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
			D3D11_MESSAGE_ID hide[] =
			{
				D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
				// TODO: Add more message IDs here as needed.
			};
			D3D11_INFO_QUEUE_FILTER filter = {};
			filter.DenyList.NumIDs = _countof(hide);
			filter.DenyList.pIDList = hide;
			d3dInfoQueue->AddStorageFilterEntries(&filter);
		}
	}
#endif

	DX::ThrowIfFailed(device.As(&m_d3dDevice));
	DX::ThrowIfFailed(context.As(&m_d3dDeviceContext));
}

void Graphics::CreateResources()
{
	ID3D11RenderTargetView* nullViews[] = { nullptr };
	m_d3dDeviceContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
	m_renderTargetView.Reset();
	m_d3dDeviceContext->Flush();

	const UINT backBufferWidth = static_cast<UINT>(m_backBufferWidth);
	const UINT backBufferHeight = static_cast<UINT>(m_backbufferHeight);
	const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	constexpr UINT backBufferCount = 2;

	// If the swap chain already exists, resize it, otherwise create one.
	if(m_swapChain)
	{
		HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

		if(hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			// If the device was removed for any reason, a new device and swap chain will need to be created.
			OnDeviceLost();

			// Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
			// and correctly set up the new device.
			return;
		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}
	else
	{
		// First, retrieve the underlying DXGI Device from the D3D Device.
		ComPtr<IDXGIDevice1> dxgiDevice;
		DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

		// Identify the physical adapter (GPU or card) this device is running on.
		ComPtr<IDXGIAdapter> dxgiAdapter;
		DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

		// And obtain the factory object that created it.
		ComPtr<IDXGIFactory2> dxgiFactory;
		DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

		// Create a descriptor for the swap chain.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
		swapChainDesc.Width = backBufferWidth;
		swapChainDesc.Height = backBufferHeight;
		swapChainDesc.Format = backBufferFormat;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = backBufferCount;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
		fsSwapChainDesc.Windowed = TRUE;

		// Create a SwapChain from a Win32 window.
		DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
			m_d3dDevice.Get(),
			m_window,
			&swapChainDesc,
			&fsSwapChainDesc,
			nullptr,
			m_swapChain.ReleaseAndGetAddressOf()
		));

		// This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
		DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
	}

	// Obtain the backbuffer for this window which will be the final 3D rendertarget.
	ComPtr<ID3D11Texture2D> backBuffer;
	DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

	// Create a view interface on the rendertarget to use on bind.
	DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

	// create samplerstate description
	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sd.MaxAnisotropy = (m_d3dDevice->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1)?D3D11_MAX_MAXANISOTROPY:2;
	sd.MaxLOD = D3D11_FLOAT32_MAX;
	sd.ComparisonFunc = D3D11_COMPARISON_NEVER;

	DX::ThrowIfFailed(m_d3dDevice->CreateSamplerState(&sd, &m_samplerState));

	// Clear the blend state description.
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(D3D11_BLEND_DESC));

	// Create an alpha enabled blend state description.
	bsd.RenderTarget[0].BlendEnable = TRUE;
	//bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bsd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bsd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bsd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bsd.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	// Create the blend state using the description.
	DX::ThrowIfFailed(m_d3dDevice->CreateBlendState(&bsd, &m_alphaEnabledBlendState));

	bsd.RenderTarget[0].BlendEnable = TRUE;
	DX::ThrowIfFailed(m_d3dDevice->CreateBlendState(&bsd, &m_alphaDisabledBlendState));

	if(m_d3dDeviceContext)
		m_spriteBatch = std::make_shared<SpriteBatch>(m_d3dDeviceContext.Get());
}

void Graphics::Begin()
{
	m_d3dDeviceContext->ClearRenderTargetView(m_renderTargetView.Get(), BackColor);
	m_d3dDeviceContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), nullptr);	

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_backBufferWidth), static_cast<float>(m_backbufferHeight));
	m_d3dDeviceContext->RSSetViewports(1, &viewport);
	
	m_spriteBatch->Begin(SpriteSortMode_FrontToBack, m_alphaEnabledBlendState.Get(), m_samplerState.Get());

	TurnOnAlphaBlending();
}

void Graphics::PresentBackBuffer()
{
	TurnOffAlphaBlending();

	m_spriteBatch->End();
	HRESULT hr = m_swapChain->Present(1, 0);

	// If the device was reset we must completely reinitialize the renderer.
	if(hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		OnDeviceLost();
	}
	else
	{
		DX::ThrowIfFailed(hr);
	}
}

void Graphics::OnDeviceLost()
{
	AssetLoader::OnDeviceLost();

	m_alphaDisabledBlendState.Reset();
	m_alphaEnabledBlendState.Reset();
	m_renderTargetView.Reset();
	m_swapChain.Reset();
	m_d3dDeviceContext.Reset();
	m_d3dDevice.Reset();

	CreateDevice();

	CreateResources();
}

void Graphics::SetWidth(int width)
{
	m_backBufferWidth = width;
}

void Graphics::SetHeight(int height)
{
	m_backbufferHeight = height;
}

void Graphics::TurnOnAlphaBlending()
{
	float blendFactor[4] = { 0 };

	m_d3dDeviceContext->OMSetBlendState(m_alphaEnabledBlendState.Get(), blendFactor, 0xffffffff);
}

void Graphics::TurnOffAlphaBlending()
{
	float blendFactor[4] = { 0 };

	m_d3dDeviceContext->OMSetBlendState(m_alphaDisabledBlendState.Get(), blendFactor, 0xffffffff);
}
