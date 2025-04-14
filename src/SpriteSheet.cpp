#include "SpriteSheet.h"

#include "Graphics.h"
#include "Sprite.h"
#include "SpriteFrameData.h"
#include "Texture.h"

#include <directxtk/SpriteBatch.h>
#include <vector>

Spritesheet::Spritesheet()
{
	m_frames.clear();
}

Spritesheet::~Spritesheet()
{
	m_frames.clear();
}

void Spritesheet::Init(Texture* texture, std::vector<SpriteFrameData> spriteFrameData)
{
	Sprite::Init(texture);

	m_frames = spriteFrameData;
}

void Spritesheet::Render(Graphics* graphics, int frameNum)
{
	if(!m_enabled) return;

	graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(), m_position, &m_frames[frameNum].frame, m_colour,
									 m_rotation, OffsetOrigin(frameNum), m_scale, m_spriteEffects, m_depth);
}

void Spritesheet::Render(Graphics* graphics, Vector2 position, int frameNum)
{
	if(!m_enabled) return;

	graphics->GetDefaultSpriteBatch()->Draw(m_texture->GetTexture(), position, &m_frames[frameNum].frame, m_colour,
									 m_rotation, OffsetOrigin(frameNum), m_scale, m_spriteEffects, m_depth);
}

Vector2 Spritesheet::OffsetOrigin(unsigned int frameNum)
{
	Vector2 origin = m_origin;

	if(m_spriteEffects != SpriteEffects_FlipHorizontally)
		return origin;
	
	auto offset = m_frames[frameNum].spriteSourceSize.right - m_frames[frameNum].spriteSourceSize.left - origin.x;
	origin.x = offset;
	return origin;
}
