#include "Texture.h"

#include "Graphics.h"
#include "Logger.h"
#include "Utils.h"

#include <DirectXTK/WICTextureLoader.h>
#include <string>
#include <Windows.h>

Texture::Texture() :
	m_texture(nullptr),
	m_resource(nullptr)
{
}

void Texture::LoadTexture(Graphics* graphics, const std::string &filename)
{
	std::wstring textureFile = Utils::ToWideString(filename);

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
	m_resource->Release();
	m_texture->Release();
}