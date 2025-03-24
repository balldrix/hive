#include "UISprite.h"

#include "Graphics.h"
#include "Sprite.h"
#include "Texture.h"

void UISprite::Render(Graphics* graphics)
{
	if(!m_enabled) return;

	graphics->GetUISpriteBatch()->Draw(m_texture->GetTexture(), 
		m_position,
		&m_rect,
		m_colour,
		m_rotation,
		m_origin,
		m_scale,
		m_spriteEffects,
		m_depth);
}
