// Texture.h
// Christopher Ball 2016
// a class to load and store textures
// for use in Sprites

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "pch.h"

// forward declarations
class Graphics;

class Texture
{
public:
	Texture();
	~Texture();
	void LoadTexture(Graphics* graphics, std::string filename); // load texture from file
	ID3D11ShaderResourceView*	GetTexture() { return m_texture; } // return pointer to shader resource view
	ID3D11Resource* GetResource() { return m_resource; } // return pointer to texture resource
	void Release(); // release shader resource

private:
	ID3D11ShaderResourceView*	m_texture; // shader resource view
	ID3D11Resource*				m_resource; // texture resource
};

#endif _TEXTURE_H_
