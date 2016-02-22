#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "TextureManager.h"
#include "AABB.h"
#include <string>

enum FACING_DIRECTION
{
	LEFT,
	RIGHT
};

class Sprite
{
public:
	Sprite();
	~Sprite();
	virtual bool				Init(Graphics* graphics, TextureManager* textureManager);
	virtual void				Update(float deltaTime);
	virtual	void				Render();
	virtual	void				Render(Vector2D position);
	virtual	void				Render(Vector2D position, RECT rect);
	void						RenderHitBox(AABB box);

	virtual	void				SetID(const char* ID);
	virtual	void				SetTransKey(int r, int g, int b);
	virtual void				SetRect();
	virtual	void				SetRect(RECT rect);
	virtual	void				SetRect(int left, int right, int top , int bottom);
	virtual	void				SetVerticalFlip(bool vFlip);
	virtual	void				SetHorizontalFlip(bool hFlip);

	virtual	void				SetWidth(int w);
	virtual	void				SetHeight(int h);

	void						SetCurrentFrame(unsigned int frame);
	void						SetShowHitBox(bool showHitBox);

	void						SetFacingDirection(FACING_DIRECTION direction);
	void						FlipSprite();
	virtual void				Reset();

	virtual	RECT				GetRect()					const { return m_spriteData.rect; }
	AABB						GetAABB()					const { return m_collisionBox; }
	bool						GetShowHitBox()				const { return m_showHitBox; }

	virtual	unsigned int		GetWidth()					const
	{
		return m_spriteData.width;
	}
	virtual	unsigned int		GetHeight()					const
	{
		return m_spriteData.height;
	}

protected:
	Graphics*					m_pGraphics;
	TextureManager*				m_pTextureManager;
	
	SpriteData					m_spriteData;

	unsigned int				m_numCols;
	unsigned int				m_currentFrame;

	AABB						m_collisionBox;

	bool						m_initialised;
	bool						m_showHitBox;
	
	HRESULT						m_result;

	D3DCOLOR					m_colourFilter;
	D3DCOLOR					m_transKey;

	FACING_DIRECTION			m_facingDirection;

	CustomVertex				m_vertex[5];
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;
};

#endif _SPRITE_H_