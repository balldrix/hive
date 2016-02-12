#include "Surface.h"
#include <time.h>

Surface::Surface() :
	m_pGraphics(NULL),
	m_pSurface(NULL),
	m_width(0),
	m_height(0),
	m_positionX(0),
	m_positionY(0)
{
	m_surfaceRect.top = 0;
	m_surfaceRect.left = 0;
	m_surfaceRect.bottom = 0;
	m_surfaceRect.right = 0;

	m_colour = colourNS::WHITE;
}

Surface::~Surface()
{
	Release();
}

void
Surface::Init(Graphics* graphics, int width, int height)
{
	m_pGraphics = graphics;
	m_width = width;
	m_height = height;

	m_result = m_pGraphics->GetD3DDevice()->CreateOffscreenPlainSurface(
		m_width, m_height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &m_pSurface, NULL);
}

void
Surface::Render()
{
	m_pGraphics->GetD3DDevice()->ColorFill(m_pSurface, NULL, m_colour);

	m_surfaceRect.left = (LONG)m_positionX;
	
	m_surfaceRect.top = (LONG)m_positionY;
	
	m_surfaceRect.right = (LONG)(m_positionX + m_width);
	
	m_surfaceRect.bottom = (LONG)(m_positionY + m_height);
	
	m_pGraphics->GetD3DDevice()->StretchRect(
		m_pSurface, NULL, m_pGraphics->GetBackBuffer(), &m_surfaceRect, D3DTEXF_NONE);
}

void
Surface::Release()
{
	if (m_pSurface != NULL)
	{
		m_pSurface->Release();
		m_pSurface = NULL;
	}
}

void
Surface::SetColour(D3DCOLOR c)
{
	m_colour = c;
}

void
Surface::SetPositionX(unsigned int x)
{
	m_positionX = x;
}

void
Surface::SetPositionY(unsigned int y)
{
	m_positionY = y;
}