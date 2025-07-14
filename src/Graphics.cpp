#include "Graphics.h"

#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "Logger.h"

#include <combaseapi.h>
#include <cstdlib>
#include <d3d11.h>
#include <d3d11sdklayers.h>
#include <d3dcommon.h>
#include <directxtk/SpriteBatch.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgiformat.h>
#include <memory>
#include <minwinbase.h>
#include <vector>
#include <windows.h>
#include <wrl/client.h>
#include <windef.h>

using namespace GlobalConstants;
using namespace DirectX;

using Microsoft::WRL::ComPtr;

Graphics::Graphics() :
	m_window(nullptr),
	m_hInstance(nullptr),
	m_featureLevel(D3D_FEATURE_LEVEL_9_1),
	m_fullscreen(false),
	m_backbufferWidth(0),
	m_backbufferHeight(0),
	m_windowWidth(0),
	m_windowHeight(0),
	m_displayModes()
{
}

Graphics::~Graphics() { }

void Graphics::Init(int windowWidth, int windowHeight, HWND hWnd, HINSTANCE hInstance)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	m_backbufferWidth = GameWidth;
	m_backbufferHeight = GameHeight;

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
		nullptr,							// specify nullptr to use the default adapter
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		device.ReleaseAndGetAddressOf(),	// returns the Direct3D device created
		&m_featureLevel,					// returns feature level of device created
		context.ReleaseAndGetAddressOf()	// returns the device immediate context
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
	// Unbind all views from the pipeline
	m_d3dDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	m_d3dDeviceContext->ClearState();
	m_d3dDeviceContext->Flush();
	m_renderRTV.Reset();
	m_renderTextureSRV.Reset();
	m_renderTexture.Reset();
	m_presentRTV.Reset();
	m_backbuffer.Reset();

	const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	constexpr UINT backBufferCount = 2;

	// If the swap chain already exists, resize it, otherwise create one.
	if(m_swapChain)
	{
		HRESULT hr = m_swapChain->ResizeBuffers(
			backBufferCount,
			m_windowWidth,
			m_windowHeight,
			backBufferFormat,
			0
		);

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
		swapChainDesc.Width = m_windowWidth;
		swapChainDesc.Height = m_windowHeight;
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

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = m_backbufferWidth;
	texDesc.Height = m_backbufferHeight;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	// Get the swap chain texture for presentation
	DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(m_backbuffer.GetAddressOf())));
	DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(m_backbuffer.Get(), nullptr, m_presentRTV.ReleaseAndGetAddressOf()));

	// Create the internal render texture
	DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&texDesc, nullptr, m_renderTexture.GetAddressOf()));
	DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(m_renderTexture.Get(), nullptr, m_renderRTV.GetAddressOf()));
	DX::ThrowIfFailed(m_d3dDevice->CreateShaderResourceView(m_renderTexture.Get(), nullptr, m_renderTextureSRV.GetAddressOf()));

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

	if(!m_d3dDeviceContext) return;

	m_defaultSpriteBatch = std::make_shared<SpriteBatch>(m_d3dDeviceContext.Get());
	m_uiSpriteBatch = std::make_shared<SpriteBatch>(m_d3dDeviceContext.Get());

	UpdateDisplayModes();
}

void Graphics::Begin()
{
	m_d3dDeviceContext->ClearRenderTargetView(m_renderRTV.Get(), BackColor);
	m_d3dDeviceContext->OMSetRenderTargets(1, m_renderRTV.GetAddressOf(), nullptr);

	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<float>(m_backbufferWidth);
	vp.Height = static_cast<float>(m_backbufferHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_d3dDeviceContext->RSSetViewports(1, &vp);
	
	m_defaultSpriteBatch->Begin(SpriteSortMode_FrontToBack, m_alphaEnabledBlendState.Get(), m_samplerState.Get());
	m_uiSpriteBatch->Begin(SpriteSortMode_FrontToBack, m_alphaEnabledBlendState.Get(), m_samplerState.Get());

	TurnOnAlphaBlending();
}

void Graphics::PresentBackBuffer()
{
	TurnOffAlphaBlending();

	m_defaultSpriteBatch->End();
	m_uiSpriteBatch->End();

	m_d3dDeviceContext->OMSetRenderTargets(1, m_presentRTV.GetAddressOf(), nullptr);

	// Clear to black for letterboxing
	const float black[4] = { 0, 0, 0, 1 };
	m_d3dDeviceContext->ClearRenderTargetView(m_presentRTV.Get(), black);

	RECT rc;
	GetClientRect(m_window, &rc);
	float windowWidth = static_cast<float>(rc.right - rc.left);
	float windowHeight = static_cast<float>(rc.bottom - rc.top);

	D3D11_VIEWPORT vp = {};
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = static_cast<float>(windowWidth);
	vp.Height = static_cast<float>(windowHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	m_d3dDeviceContext->RSSetViewports(1, &vp);

	float targetAspect = static_cast<float>(m_backbufferWidth) / m_backbufferHeight;
	float windowAspect = static_cast<float>(windowWidth) / windowHeight;

	float scale = (windowAspect > targetAspect)
		? static_cast<float>(windowHeight) / m_backbufferHeight
		: static_cast<float>(windowWidth) / m_backbufferWidth;

	float drawWidth = m_backbufferWidth * scale;
	float drawHeight = m_backbufferHeight * scale;
	float offsetX = (windowWidth - drawWidth) * 0.5f;
	float offsetY = (windowHeight - drawHeight) * 0.5f;

	XMFLOAT2 drawPos(offsetX, offsetY);
	XMFLOAT2 scaleVec(scale, scale);


	m_defaultSpriteBatch->Begin(SpriteSortMode_Deferred, nullptr, m_samplerState.Get());
	m_defaultSpriteBatch->Draw(m_renderTextureSRV.Get(), drawPos, nullptr, Colors::White, 0.0f, {}, scaleVec);
	m_defaultSpriteBatch->End();

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
	m_renderRTV.Reset();
	m_swapChain.Reset();
	m_d3dDeviceContext.Reset();
	m_d3dDevice.Reset();

	CreateDevice();
	CreateResources();
}

void Graphics::SetResolution(int width, int height)
{
	if(width == m_windowWidth && height == m_windowHeight)
		return;

	m_windowWidth = width;
	m_windowHeight = height;

	CreateResources();
}


void Graphics::UpdateDisplayModes()
{
	std::vector<DisplayMode> tempModes;

	DEVMODE dm = {};
	dm.dmSize = sizeof(dm);
	int i = 0;

	while(EnumDisplaySettings(NULL, i++, &dm))
	{
		if(!(dm.dmFields & DM_PELSWIDTH) || !(dm.dmFields & DM_PELSHEIGHT)) continue;
		if(dm.dmBitsPerPel != 32) continue;
		if(dm.dmDisplayFrequency < 60) continue;

		bool replaced = false;
		for(auto& mode : tempModes) {
			if(mode.width == dm.dmPelsWidth && mode.height == dm.dmPelsHeight) {
				if(dm.dmDisplayFrequency > mode.refreshRate) {
					mode.refreshRate = dm.dmDisplayFrequency;
				}
				replaced = true;
				break;
			}
		}

		if (!replaced) {
			DisplayMode displayMode = { 0 };
			displayMode.width = dm.dmPelsWidth;
			displayMode.height = dm.dmPelsHeight;
			displayMode.refreshRate = dm.dmDisplayFrequency;
			tempModes.push_back(displayMode);
		}

		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
	}

	m_displayModes.clear();
	m_displayModes = tempModes;
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
