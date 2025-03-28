#include "Sprite.h"

#include "Graphics.h"
#include "Texture.h"

Sprite::Sprite() :
	m_texture(nullptr),
	m_position(0.0f, 0.0f),
	m_scale(0.0f),
	m_rotation(0.0f),
	m_alpha(0.0f),
	m_colour(Colors::White.v),
	m_origin(0.0f, 0.0f),
	m_rect(),
	m_spriteEffects(SpriteEffects::SpriteEffects_None),
	m_width(0),
	m_height(0),
	m_depth(0.0f),
	m_enabled(true)
{
}

Sprite::~Sprite()
{
}

void Sprite::Init(Texture* texture)
{
	m_texture = texture;

	ID3D11Texture2D* tex2D;
	tex2D = (ID3D11Texture2D*)m_texture->GetResource();

	D3D11_TEXTURE2D_DESC desc;
	tex2D->GetDesc(&desc);
	
#ifndef _DEBUG
	tex2D->Release();
#endif

	m_width = desc.Width;
	m_height = desc.Height;

	m_rect.top = (LONG)0.0f;
	m_rect.left = (LONG)0.0f;
	m_rect.right = (LONG)m_width;
	m_rect.bottom = (LONG)m_height;

	m_origin.x = m_width / 2.0f;
	m_origin.y = m_height / 2.0f;

	m_scale = 1.0f;
	m_alpha = 1.0f;
}

void Sprite::Render(Graphics* graphics)
{
	if(!m_enabled)
		return;

	graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(),
		m_position,
		&m_rect,
		m_colour,
		m_rotation,
		m_origin,
		m_scale,
		m_spriteEffects,
		m_depth);
}

void Sprite::Render(Graphics* graphics, float alpha)
{
	if(!m_enabled)
		return;

	SetAlpha(alpha);
	Render(graphics);
}

void
Sprite::Render(Graphics* graphics, const Vector2& position)
{
	if(!m_enabled)
		return;

	// draw sprite
	graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(),
		position,
		&m_rect,
		m_colour,
		m_rotation,
		m_origin,
		m_scale,
		m_spriteEffects,
		m_depth);
}

void Sprite::Render(Graphics* graphics, const Vector2& position, const RECT& destination)
{
	if(!m_enabled)
		return;

	// set alpha colour key
	m_colour.w = m_alpha;

	SetPosition(position);

	// draw sprite
	//graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(), destination, m_colour);
	graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(), destination, &m_rect,
		m_colour,
		m_rotation,
		m_origin,
		m_spriteEffects,
		m_depth);
}

void Sprite::EnableSprite()
{
	m_enabled = true;
}

void Sprite::DisableSprite()
{
	m_enabled = false;
}

void Sprite::SetPosition(const Vector2& position)
{
	// round position as object position will be floating points
	// and pixel positions are ints
	m_position.x = round(position.x);
	m_position.y = round(position.y);
}

void Sprite::SetScale(const float& scale)
{
	m_scale = scale;
}

void Sprite::SetRotation(const float& rotation)
{
	m_rotation = rotation;
}

void Sprite::SetAlpha(const float& alpha)
{
	m_alpha = alpha;
	SetColour(m_colour);
}

void Sprite::SetColour(const Color& colour)
{
	m_colour = colour;
	m_colour.w = m_alpha;
}

void Sprite::SetOrigin(const Vector2& origin)
{
	m_origin = origin;
}

void Sprite::SetSourceRect(const RECT& rect)
{
	m_rect = rect;
}

void Sprite::SetFlipEffect(SpriteEffects effect)
{
	m_spriteEffects = effect;
}

void Sprite::SetDepth(const float& depth)
{
	m_depth = depth;
}