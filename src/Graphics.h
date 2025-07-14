#pragma once

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcommon.h>
#include <directxtk/SpriteBatch.h>
#include <directxtk/VertexTypes.h>
#include <dxgi1_2.h>
#include <exception>
#include <memory>
#include <vector>
#include <windows.h>
#include <wrl/client.h>

namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if(FAILED(hr))
		{
			throw std::exception();
		}
	}
}

using namespace DirectX;
using VertexType = DirectX::VertexPositionColor;

class Graphics
{
public:
	Graphics();
	~Graphics();

	Graphics(Graphics&&) = default;
	Graphics& operator= (Graphics&&) = default;

	Graphics(Graphics const&) = delete;
	Graphics& operator= (Graphics const&) = delete;

	void Init(int windowWidth, int windowHeight, HWND hWindow, HINSTANCE hInstance);
	void CreateDevice();
	void CreateResources();

	void Begin();
	
	void PresentBackBuffer();

	void OnDeviceLost();

	Microsoft::WRL::ComPtr<ID3D11Device1> GetDevice() const { return m_d3dDevice; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return m_d3dDeviceContext; }
	Microsoft::WRL::ComPtr<IDXGISwapChain1> GetSwapChain() const { return m_swapChain; }
	std::shared_ptr<SpriteBatch> GetDefaultSpriteBatch() const { return m_defaultSpriteBatch; }
	std::shared_ptr<SpriteBatch> GetUISpriteBatch() const { return m_uiSpriteBatch; }

	int GetBackbufferWidth()	const { return m_nativeGameWidth; }
	int GetBackbufferHeight()	const { return m_nativeGameHeight; }
	int GetOutputWidth() const { return m_windowWidth; }
	int GetOutputHeight() const { return m_windowHeight; }

	HWND GetHwnd() const { return m_window; }
	HINSTANCE GetHInstance() const { return m_hInstance; }

	void SetResolution(int width, int height);

	struct DisplayMode
	{
		int width;
		int height;
		int refreshRate;
	};

	std::vector<DisplayMode> GetSupportedResolutions() const {	return m_displayModes; };

private:
	void UpdateDisplayModes();
	void TurnOnAlphaBlending();
	void TurnOffAlphaBlending();

	HWND m_window;
	HINSTANCE m_hInstance;
	
	D3D_FEATURE_LEVEL m_featureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dDeviceContext;
	
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderRTV;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_presentRTV;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backbuffer;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_renderTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_renderTextureSRV;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_samplerState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaEnabledBlendState;
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaDisabledBlendState;

	std::shared_ptr<SpriteBatch> m_defaultSpriteBatch;
	std::shared_ptr<SpriteBatch> m_uiSpriteBatch;

	int m_nativeGameWidth;
	int m_nativeGameHeight;
	int m_windowWidth;
	int m_windowHeight;
	std::vector<DisplayMode> m_displayModes;
};
