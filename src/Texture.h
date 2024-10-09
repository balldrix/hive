#pragma once

#include "pch.h"

class Graphics;

class Texture
{
public:
	Texture();
	~Texture();
	void LoadTexture(Graphics* graphics, const std::string& filename);
	ID3D11ShaderResourceView*	GetTexture() { return m_texture; }
	ID3D11Resource* GetResource() { return m_resource; }
	void Release();

private:
	ID3D11ShaderResourceView*	m_texture;
	ID3D11Resource*				m_resource;
};
