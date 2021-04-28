#include "Texture.h"
#include "Graphics.h"
#include "Error.h"
#include "WICTextureLoader.h"

Texture::Texture() :
	m_texture(nullptr),
	m_resource(nullptr)
{
}

Texture::~Texture()
{
}

void 
Texture::LoadTexture(Graphics* graphics, std::string filename)
{
	// convert string to wstring LPCWSTR
	std::wstring textureFile = std::wstring(filename.begin(), filename.end());

	// load texture from file
	HRESULT result = CreateWICTextureFromFile(graphics->GetDevice().Get(), nullptr, textureFile.c_str(), &m_resource, &m_texture, 0);
	
	// if load result is not ok
	if(result != S_OK)
	{
		std::string error = " Error Loading texture file " + filename + " in Texture.cpp line 21; \n"; // error message
		Error::FileLog(error);
		MessageBox(graphics->GetHwnd(), L"Error loading Texture. See Logs/Error.txt", L"Error!", MB_OK); // display loading texture error message
		PostQuitMessage(0); // quit game
	}
}

void
Texture::Release()
{
	// release texture resources

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