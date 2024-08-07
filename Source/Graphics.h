#pragma once

#include "pch.h"

using VertexType = DirectX::VertexPositionColor;

class Shader;

class Graphics
{
public:
	Graphics();					
	~Graphics();

	Graphics(Graphics&&) = default;
	Graphics& operator= (Graphics&&) = default;

	Graphics(Graphics const&) = delete;
	Graphics& operator= (Graphics const&) = delete;

	void Init(HWND hWindow, HINSTANCE hInstance);
	void CreateDevice();
	void CreateResources();
								
	void Begin();
	
	void PresentBackBuffer();

	void OnDeviceLost();

	Microsoft::WRL::ComPtr<ID3D11Device1> GetDevice() const { return m_d3dDevice; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return m_d3dDeviceContext; }
	Microsoft::WRL::ComPtr<IDXGISwapChain1> GetSwapChain() const { return m_swapChain; }
	std::shared_ptr<SpriteBatch> GetSpriteBatch() const { return m_spriteBatch; }

	int GetWidth()	const { return m_backBufferWidth; }
	int GetHeight()	const { return m_backBufferHeight; }
	
	HWND GetHwnd()	const { return m_window; }		
	HINSTANCE GetHInstance() const { return m_hInstance; }
	bool GetFullscreen() const { return m_fullscreen; }

	void SetWorldMatrix(Matrix worldMatrix);
	void SetViewMatrix(Matrix viewMatrix);
	void SetProjectionMatrix(Matrix projectionMatrix);

	void SetLightPositions(XMFLOAT4 lightPositions[]);
	void SetLightColors(XMFLOAT4 lightColors[]);

	void SetWidth(int width);
	void SetHeight(int height);

private:
	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	HWND m_window;				
	HINSTANCE m_hInstance;		
	
	D3D_FEATURE_LEVEL m_featureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;
	
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backbuffer;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthBuffer;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_defaultRasterState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaEnabledBlendState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaDisabledBlendState;

	ID3D11Buffer* m_constantBufferWorld;
	ID3D11Buffer* m_constantBufferView;
	ID3D11Buffer* m_constantBufferProjection;
	ID3D11Buffer* m_constantBufferLightPositions;
	ID3D11Buffer* m_constantBufferLightColors;

	std::shared_ptr<SpriteBatch> m_spriteBatch;

	bool m_fullscreen;		
	int m_backBufferWidth;		
	int m_backBufferHeight;		
};
