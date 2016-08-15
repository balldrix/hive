#include "Texture.h"
#include "Graphics.h"

Texture::Texture() :
m_pTexture(NULL),
m_pGraphics(NULL),
m_colourKey(Colors::Magenta),
m_filename(NULL),
m_height(0),
m_width(0),
m_initialised(false)
{

}

Texture::~Texture()
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

bool
Texture::Init(Graphics* graphics, const wchar_t* filename)
{
	m_pGraphics = graphics;
	m_filename = filename;

	// d3d image info struct
	D3DXIMAGE_INFO imageInfo;

	m_result = D3DXGetImageInfoFromFile(filename, &imageInfo);

	if(m_result != S_OK)
	{
		// TODO deal with error reporting
	}

	// get texture dimensions from imageInfo
	m_width = imageInfo.Width;
	m_height = imageInfo.Height;
	
	m_result = D3DXCreateTextureFromFileEx(
				m_pGraphics->GetD3DDevice(),
				filename,
				imageInfo.Width,
				imageInfo.Height,
				1, 0,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				m_colourKey.BGRA(),
				&imageInfo,
				NULL, &m_pTexture);
	
	if(m_result != S_OK)
	{
		// TODO deal with error reporting
		if(m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
		return false;
	}
	m_initialised = true;
	return true;
}

void
Texture::OnLostDevice()
{
	if (!m_initialised)
	{
		return;
	}

	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void
Texture::OnResetDevice()
{
	if (!m_initialised)
	{
		return;
	}

	Init(m_pGraphics, m_filename);
}