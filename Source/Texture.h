#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "pch.h"

// forward declarations
class Graphics;

#define WIN32_LEAN_AND_MEAN

class Texture
{
public:
	Texture();
	virtual ~Texture();

	bool				Init(Graphics* graphics, const wchar_t* filename);

	LPDIRECT3DTEXTURE9	GetTexture() const	{ return m_pTexture; }

	UINT				GetWidth() const	{ return m_width; }
	UINT				GetHeight() const	{ return m_height; }

	void				OnLostDevice();
	void				OnResetDevice();

private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	Graphics*			m_pGraphics;

	const wchar_t*		m_filename;
	Color				m_colourKey;
	UINT				m_width;
	UINT				m_height;
	bool				m_initialised;

	HRESULT				m_result;
};

#endif _TEXTURE_H_