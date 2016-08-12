#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_
#define WIN32_LEAN_AND_MEAN

#include "Graphics.h"
#include "Constants.h"

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	bool				Init(Graphics* graphics, const char* fileName);

	LPDIRECT3DTEXTURE9	GetTexture() const	{ return m_pTexture; }

	UINT				GetWidth() const	{ return m_width; }
	UINT				GetHeight() const	{ return m_height; }

	void				OnLostDevice();
	void				OnResetDevice();

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	Graphics*		m_pGraphics;

	const char* m_fileName;
	D3DCOLOR	m_colourKey;
	UINT		m_width;
	UINT		m_height;
	bool		m_initialised;

	HRESULT	m_result;
};

#endif _TEXTUREMANAGER_H_