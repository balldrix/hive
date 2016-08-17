#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Graphics.h"
#include "Texture.h"
#include "AABB.h"
#include <string>

// structure to store properties of a sprite
struct SpriteData
{
	int					width;
	int					height;
	Vector2				position;
	float				scale;
	float				angle;
	RECT				rect;
	LPDIRECT3DTEXTURE9	texture;
	bool				flipHorizontal;
	bool				flipVertical;
};

enum FACING_DIRECTION
{
	LEFT,
	RIGHT
};

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();
	virtual void				Init(Graphics* graphics, Texture* textureManager, unsigned int frameWidth, unsigned int frameHeight);
	virtual void				Update(float deltaTime);
	virtual void				Render();
	virtual void				Render(Vector2 position);
	virtual void				Render(Vector2 position, RECT rect);
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
	Texture*					m_pTextureManager;
	
	SpriteData					m_spriteData;

	unsigned int				m_numCols;
	unsigned int				m_currentFrame;

	AABB						m_collisionBox;

	bool						m_initialised;
	bool						m_showHitBox;
	
	HRESULT						m_result;

	Color						m_colourFilter;
	Color						m_transKey;

	FACING_DIRECTION			m_facingDirection;

};

#endif _SPRITE_H_