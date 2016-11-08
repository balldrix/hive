// Sprite.h
// Christopher Ball 2016
// sprite class contains texture, position, alpha
// rotation and scale of the 2D sprite

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "pch.h"

// forward declarations
class Graphics;
class Texture;

class Sprite
{
public:
	Sprite();
	~Sprite();
	void				Init(Texture* texture); // initialise sprite
	void				Render(Graphics* graphics); // render sprite
	void				Render(Graphics* graphics, Vector2 position); // render sprite

	// helper methods
	// setters
	void				SetPosition(const Vector2& position);
	void				SetScale(const float& scale); 
	void				SetRotation(const float& rotation); 
	void				SetAlpha(const float& alpha);
	void				SetColour(const Color& colour);
	void				SetOrigin(const Vector2& origin);
	void				SetRect(const RECT& rect);
	void				SetActive(bool active);

	// getters
	const Vector2		GetPosition() const		{ return m_position; }
	const float			GetScale() const		{ return m_scale; }
	const float			GetRotation() const		{ return m_rotation; }
	const float			GetAlpha() const		{ return m_alpha; }
	const Color			GetColour() const		{ return m_colour; }
	const Vector2		GetOrigin() const		{ return m_origin; }
	const RECT			GetRect() const			{ return m_rect; }
	const UINT			GetWidth() const		{ return m_width; }
	const UINT			GetHeight() const		{ return m_height; }
	const bool			GetActive() const		{ return m_active; }

private:
	Texture*			m_texture;	// texture pointer

	Vector2				m_position; // sprite position
	float				m_scale;	// scaler
	float				m_rotation; // rotation angle in radians
	float				m_alpha;	// alpha value 0.0f - 1.0f
	Color				m_colour;	// colour tint
	Vector2				m_origin;	// sprite origin i.e. middle
	RECT				m_rect;		// source rect

	UINT				m_width;	// sprite width
	UINT				m_height;	// sprite height
	
	bool				m_active;	// if active or not
};

#endif _SPRITE_H_