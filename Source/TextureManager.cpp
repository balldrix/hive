#include "TextureManager.h"

TextureManager::TextureManager() :
m_pTexture(NULL),
m_pGraphics(NULL),
m_colourKey(colourNS::MAGENTA),
m_fileName(NULL),
m_height(0),
m_width(0),
m_initialised(false)
{

}

TextureManager::~TextureManager()
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

bool
TextureManager::Init(Graphics* graphics, const char* fileName)
{
	m_pGraphics = graphics;
	m_fileName = fileName;

	m_result = m_pGraphics->LoadTexture(
				m_fileName, 
				m_pTexture,
				m_colourKey,
				m_width, m_height);

	if (m_result != S_OK)
	{
		if (m_pTexture != NULL)
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
TextureManager::OnLostDevice()
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
TextureManager::OnResetDevice()
{
	if (!m_initialised)
	{
		return;
	}

	m_pGraphics->LoadTexture(
		m_fileName,
		m_pTexture,
		m_colourKey,
		m_width, m_height);
}