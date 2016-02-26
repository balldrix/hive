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

struct TileSize
{
	unsigned int x;
	unsigned int y;
};

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();
	virtual void				Init(Graphics* graphics, TextureManager* textureManager);
	virtual void				Update(float deltaTime);
	virtual void				Render();
	virtual void				Render(Vector2D position);
	virtual void				Render(Vector2D position, RECT rect);
	virtual void				Reset();
	
	void						RenderHitBox(AABB box);

	void						SetTransKey(int r, int g, int b);
	void						SetRect();
	void						SetRect(RECT rect);
	void						SetRect(int left, int right, int top , int bottom);
	void						SetVerticalFlip(bool vFlip);
	void						SetHorizontalFlip(bool hFlip);

	void						SetWidth(int w);
	void						SetHeight(int h);

	void						SetCurrentFrame(unsigned int frame);
	void						SetShowHitBox(bool showHitBox);

	void						SetFacingDirection(FACING_DIRECTION direction);
	void						FlipSprite();

	virtual	RECT				GetRect()					const { return m_spriteData.rect; }
	AABB						GetAABB()					const { return m_collisionBox; }
	bool						GetShowHitBox()				const { return m_showHitBox; }

	unsigned int				GetWidth()					const {	return m_spriteData.width; }
	unsigned int				GetHeight()					const { return m_spriteData.height; }

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
	TileSize					m_tileSize;

	CustomVertex				m_vertex[5];
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;
};

#endif _SPRITE_H_