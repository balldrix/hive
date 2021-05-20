#pragma once

#include "pch.h"

class Graphics;

class Texture
{
public:
	Texture();
	~Texture();
	void LoadTexture(Graphics* graphics, const std::string &filename); // load texture from file
	ID3D11ShaderResourceView*	GetTexture() { return m_texture; } // return pointer to shader resource view
	ID3D11Resource* GetResource() { return m_resource; } // return pointer to texture resource
	void Release(); // release shader resource

private:
	ID3D11ShaderResourceView*	m_texture; // shader resource view
	ID3D11Resource*				m_resource; // texture resource
};
