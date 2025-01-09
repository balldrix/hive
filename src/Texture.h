#pragma once

#include <d3d11.h>
#include <string>

class Graphics;

class Texture
{
public:
	Texture();
	~Texture() = default;

	void LoadTexture(Graphics* graphics, const std::string& filename);
	ID3D11ShaderResourceView*	GetTexture() { return m_texture; }
	ID3D11Resource* GetResource() { return m_resource; }
	virtual void Release();

protected:
	ID3D11ShaderResourceView*	m_texture;
	ID3D11Resource*				m_resource;
};
