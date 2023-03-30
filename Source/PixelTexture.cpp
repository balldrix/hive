#include "PixelTexture.h"

#include "Graphics.h"

PixelTexture::PixelTexture()
{
}

PixelTexture::~PixelTexture()
{
	m_texture->Release();
}

void PixelTexture::Init(Graphics* graphics)
{
	static const uint32_t WHITE_PIXEL = 0xffffffff;

	D3D11_SUBRESOURCE_DATA initData =
	{
		&WHITE_PIXEL, sizeof(uint32_t), 0
	};

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = 1;
	desc.Height = 1;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	HRESULT hr = graphics->GetDevice()->CreateTexture2D(&desc, &initData, &texture);

	DX::ThrowIfFailed(hr);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = graphics->GetDevice()->CreateShaderResourceView(texture.Get(), &srvDesc, &m_texture);

	DX::ThrowIfFailed(hr);
}