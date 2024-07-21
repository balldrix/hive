#include "Graphics.h"

#include "pch.h"
#include "Window.h"
#include "GlobalConstants.h"
#include "ConstantBuffers.h"
#include "Error.h"
#include "Shader.h"

using namespace GlobalConstants;
using namespace DirectX;
using namespace ConstantBuffers;

using Microsoft::WRL::ComPtr;

Graphics::Graphics() :
	m_window(nullptr),
	m_hInstance(nullptr),
	m_featureLevel(D3D_FEATURE_LEVEL_9_1),
	m_fullscreen(false),
	m_constantBufferWorld(nullptr),
	m_constantBufferView(nullptr),
	m_constantBufferProjection(nullptr),
	m_constantBufferLightPositions(nullptr),
	m_constantBufferLightColors(nullptr),
	m_backBufferWidth(GameWidth),
	m_backBufferHeight(GameHeight)
{
}

Graphics::~Graphics() {}

void Graphics::Init(HWND hWnd, HINSTANCE hInstance)
{
	m_window = hWnd;
	CreateDevice();
	CreateResources();
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
	const UINT backBufferHeight = static_cast<UINT>(m_backBufferHeight);
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

	// depth buffer descripton
	D3D11_TEXTURE2D_DESC t2d = { 0 };
	t2d.Width = m_backBufferWidth;
	t2d.Height = m_backBufferHeight;
	t2d.MipLevels = 1;
	t2d.ArraySize = 1;
	t2d.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	t2d.SampleDesc.Count = 1;
	t2d.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	t2d.Usage = D3D11_USAGE_DEFAULT;

	// create depth buffer
	DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&t2d, NULL, &m_depthBufferTexture));

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

	m_d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);

	// create depth stencil state
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// create depth stencil state
	D3D11_DEPTH_STENCIL_DESC svd = { 0 };

	// Set up the description of the stencil state.
	svd.DepthEnable = true;
	svd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	svd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	svd.StencilEnable = true;
	svd.StencilReadMask = 0xFF;
	svd.StencilWriteMask = 0xFF;
	svd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	svd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	svd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	svd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	svd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	svd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	svd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	svd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilState(&svd, &m_depthStencilState));
	DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(m_depthBufferTexture.Get(), &dsvd, &m_depthBuffer));

	// setup default raster state
	D3D11_RASTERIZER_DESC rd = {};
	rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthBias = 0;
	rd.DepthBiasClamp = 0.0f;
	rd.DepthClipEnable = true;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.FrontCounterClockwise = false;
	rd.MultisampleEnable = false;
	rd.ScissorEnable = false;
	rd.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state
	DX::ThrowIfFailed(m_d3dDevice->CreateRasterizerState(&rd, &m_defaultRasterState));

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

	// setup constant buffers
	D3D11_BUFFER_DESC cbd = { 0 };
	cbd = { 0 };
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0;
	cbd.ByteWidth = sizeof(WorldMatrixBuffer);
	DX::ThrowIfFailed(m_d3dDevice->CreateBuffer(&cbd, nullptr, &m_constantBufferWorld));

	cbd = { 0 };
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0;
	cbd.ByteWidth = sizeof(ViewMatrixBuffer);
	DX::ThrowIfFailed(m_d3dDevice->CreateBuffer(&cbd, nullptr, &m_constantBufferView));

	cbd = { 0 };
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0;
	cbd.ByteWidth = sizeof(ProjectionMatrixBuffer);
	DX::ThrowIfFailed(m_d3dDevice->CreateBuffer(&cbd, nullptr, &m_constantBufferProjection));

	cbd = { 0 };
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0;
	cbd.ByteWidth = sizeof(LightPositionBuffer);
	DX::ThrowIfFailed(m_d3dDevice->CreateBuffer(&cbd, nullptr, &m_constantBufferLightPositions));

	cbd = { 0 };
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.CPUAccessFlags = 0;
	cbd.ByteWidth = sizeof(LightColorBuffer);
	DX::ThrowIfFailed(m_d3dDevice->CreateBuffer(&cbd, nullptr, &m_constantBufferLightColors));

	if(!m_d3dDeviceContext)
		return;
	
	m_spriteBatch = std::make_shared<SpriteBatch>(m_d3dDeviceContext.Get());
}

void Graphics::Begin()
{
	auto context = m_d3dDeviceContext.Get();
	context->ClearRenderTargetView(m_renderTargetView.Get(), BackColor);
	context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthBuffer.Get());

	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_backBufferWidth), static_cast<float>(m_backBufferHeight));
	context->RSSetViewports(1, &viewport);
	
	m_spriteBatch->Begin(SpriteSortMode_FrontToBack, m_alphaEnabledBlendState.Get(), m_samplerState.Get(), nullptr, nullptr);

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
	m_constantBufferLightColors->Release();
	m_constantBufferLightPositions->Release();
	m_constantBufferProjection->Release();
	m_constantBufferView->Release();
	m_constantBufferWorld->Release();
	m_alphaDisabledBlendState.Get()->Release();
	m_alphaEnabledBlendState.Get()->Release();
	m_defaultRasterState.Get()->Release();
	m_depthStencilState.Get()->Release();
	m_depthBufferTexture.Get()->Release();
	m_depthBuffer.Get()->Release();
	m_samplerState.Get()->Release();
	m_backbuffer.Get()->Release();
	m_renderTargetView.Get()->Release();
	m_swapChain.Get()->Release();;
	m_d3dDeviceContext.Get()->Release();
	m_d3dDevice.Get()->Release();

	CreateDevice();
	CreateResources();
}

void Graphics::SetWorldMatrix(Matrix worldMatrix)
{
	WorldMatrixBuffer cb;
	cb.worldMatrix = XMMatrixTranspose(worldMatrix);
	m_d3dDeviceContext->UpdateSubresource(m_constantBufferWorld, 0, nullptr, &cb, 0, 0);
	m_d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_constantBufferWorld);
}

void Graphics::SetViewMatrix(Matrix viewMatrix)
{
	ViewMatrixBuffer cb;
	cb.viewMatrix = XMMatrixTranspose(viewMatrix);
	m_d3dDeviceContext->UpdateSubresource(m_constantBufferView, 0, nullptr, &cb, 0, 0);
	m_d3dDeviceContext->VSSetConstantBuffers(1, 1, &m_constantBufferView);
}

void Graphics::SetProjectionMatrix(Matrix projectionMatrix)
{
	ProjectionMatrixBuffer cb;
	cb.projectionMatrix = XMMatrixTranspose(projectionMatrix);
	m_d3dDeviceContext->UpdateSubresource(m_constantBufferProjection, 0, nullptr, &cb, 0, 0);
	m_d3dDeviceContext->VSSetConstantBuffers(2, 1, &m_constantBufferProjection);
}

void Graphics::SetLightPositions(XMFLOAT4 lightPositions[])
{
	LightPositionBuffer cb;
	
	for(size_t i = 0; i < NumLights; i++)
	{
		cb.lightPosition[i] = lightPositions[i];
	}

	m_d3dDeviceContext->UpdateSubresource(m_constantBufferLightPositions, 0, nullptr, &cb, 0, 0);
	m_d3dDeviceContext->VSSetConstantBuffers(3, 1, &m_constantBufferLightPositions);	
}

void Graphics::SetLightColors(XMFLOAT4 lightColors[])
{
	LightColorBuffer cb;

	for(size_t i = 0; i < NumLights; i++)
	{
		cb.diffuseColor[i] = lightColors[i];
	}

	m_d3dDeviceContext->UpdateSubresource(m_constantBufferLightColors, 0, nullptr, &cb, 0, 0);
	m_d3dDeviceContext->PSSetConstantBuffers(4, 1, &m_constantBufferLightColors);
}

void Graphics::SetWidth(int width)
{
	m_backBufferWidth = width;
}

void Graphics::SetHeight(int height)
{
	m_backBufferHeight = height;
}

void Graphics::TurnOnAlphaBlending()
{
	float blendFactor[4];

	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_d3dDeviceContext->OMSetBlendState(m_alphaEnabledBlendState.Get(), blendFactor, 0xffffffff);
}

void Graphics::TurnOffAlphaBlending()
{
	float blendFactor[4];

	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	m_d3dDeviceContext->OMSetBlendState(m_alphaDisabledBlendState.Get(), blendFactor, 0xffffffff);
}
