#include "PixelTexture.h"

#include "Graphics.h"

void PixelTexture::Init(Graphics* graphics)
{
	static const uint32_t WHITE_PIXEL = 0xffffffff;
	const uint8_t* pixelData = reinterpret_cast<const uint8_t*>(&WHITE_PIXEL);

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = 1;
	desc.Height = 1;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = pixelData;
	initData.SysMemPitch = sizeof(uint32_t);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	HRESULT hr = graphics->GetDevice()->CreateTexture2D(&desc, &initData, &texture);
	
	DX::ThrowIfFailed(hr);

	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	texture.As(&resource);

	m_resource = resource.Get();

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	hr = graphics->GetDevice()->CreateShaderResourceView(m_resource, &srvDesc, &m_texture);
	
	DX::ThrowIfFailed(hr);
}

void PixelTexture::Release()
{
	m_texture->Release();
}
