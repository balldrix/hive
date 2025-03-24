#pragma once

#include <directxtk/SimpleMath.h>
#include <directxtk/SpriteBatch.h>

using namespace DirectX;
using namespace SimpleMath;

class Graphics;
class Texture;

class Sprite
{
public:
	Sprite();
	virtual ~Sprite();
	void				Init(Texture* texture);
	virtual void		Render(Graphics* graphics);
	void				Render(Graphics* graphics, float alpha);
	void				Render(Graphics* graphics, const Vector2& position);
	void				Render(Graphics* graphics, const Vector2& position, const RECT& destination);

	void				EnableSprite();
	void				DisableSprite();

	void				SetPosition(const Vector2& position);
	void				SetScale(const float& scale); 
	void				SetRotation(const float& rotation); 
	void				SetAlpha(const float& alpha);
	void				SetColour(const Color& colour);
	void				SetOrigin(const Vector2& origin);
	void				SetSourceRect(const RECT& rect);
	void				SetFlipEffect(SpriteEffects effect);
	void				SetDepth(const float& depth);

	const Vector2		GetPosition() const		{ return m_position; }
	const float			GetScale() const		{ return m_scale; }
	const float			GetRotation() const		{ return m_rotation; }
	const float			GetAlpha() const		{ return m_alpha; }
	const Color			GetColour() const		{ return m_colour; }
	const Vector2		GetOrigin() const		{ return m_origin; }
	const RECT			GetRect() const			{ return m_rect; }
	const UINT			GetWidth() const		{ return m_width; }
	const UINT			GetHeight() const		{ return m_height; }
	const float			GetDepth() const		{ return m_depth;}

protected:
	Texture*			m_texture;

	Vector2				m_position;
	float				m_scale;
	float				m_rotation;
	float				m_alpha;
	Color				m_colour;
	Vector2				m_origin;
	RECT				m_rect;
	UINT				m_width;
	UINT				m_height;
	SpriteEffects		m_spriteEffects;
	float				m_depth;
	bool				m_enabled;
};