#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "Graphics.h"

class Surface
{
public: 
	Surface();
	~Surface();
	void Init(Graphics* graphics, int width, int height);
	void Release();
	void Render();
	
	LPDIRECT3DSURFACE9 GetSurface() { return m_pSurface; }
	unsigned int GetPositionX() { return m_positionX; }
	unsigned int GetPositionY() { return m_positionY; }

	void SetPositionX(unsigned int x);
	void SetPositionY(unsigned int y);
	void SetRect();

	void SetColour(D3DCOLOR c);

private:
	Graphics*			m_pGraphics;
	LPDIRECT3DSURFACE9	m_pSurface;
	RECT				m_surfaceRect;

	int					m_width;
	int					m_height;
	unsigned int				m_positionX;
	unsigned int				m_positionY;

	D3DCOLOR			m_colour;
	HRESULT				m_result;
};

#endif _SURFACE_H_