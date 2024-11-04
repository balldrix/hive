#include "Texture.h"

#include "Graphics.h"
#include "Logger.h"

#include <DirectXTK/WICTextureLoader.h>

Texture::Texture() :
	m_texture(nullptr),
	m_resource(nullptr)
{
}

Texture::~Texture()
{
}

void Texture::LoadTexture(Graphics* graphics, const std::string &filename)
{
	std::wstring textureFile = std::wstring(filename.begin(), filename.end());

	HRESULT result = CreateWICTextureFromFile(graphics->GetDevice().Get(), nullptr, textureFile.c_str(), &m_resource, &m_texture, 0);
	
	if(result != S_OK)
	{
		std::string error = " Error Loading texture file " + filename + " in Texture.cpp line 21.";
		Logger::LogError(error);
		MessageBox(graphics->GetHwnd(), L"Error loading Texture. See Logs/Error.txt", L"Error!", MB_OK);
		PostQuitMessage(0);
	}
}

void Texture::Release()
{
	if(m_resource)
	{
		m_resource->Release();
		m_resource = nullptr;
	}

	if(m_texture)
	{
		m_texture->Release();
		m_texture = nullptr;
	}
}