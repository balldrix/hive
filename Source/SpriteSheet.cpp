#include "SpriteSheet.h"
#include "Texture.h"
#include "Graphics.h"

SpriteSheet::SpriteSheet()
{
	m_frames.clear();
}

SpriteSheet::~SpriteSheet()
{
	m_frames.clear();
}

void SpriteSheet::Init(Texture* texture, std::string fileName)
{
	// init sprite sheet as one big sprite
	Sprite::Init(texture);

	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);

	// get frames data
	json frames = data["frames"];

	m_frames = frames.get<std::vector<SpriteFrame>>();
}

void SpriteSheet::Render(Graphics* graphics, int frameNum)
{
	graphics->GetSpriteBatch()->Draw(m_texture->GetTexture(), m_position, &m_frames[frameNum].sourceRect, m_colour,
									 m_rotation, m_frames[frameNum].origin, m_scale, m_spriteEffects);
									 
}

void SpriteSheet::Render(Graphics* graphics, Vector2 position, int frameNum)
{
	graphics->GetSpriteBatch()->Draw(m_texture->GetTexture(), position, &m_frames[frameNum].sourceRect, m_colour,
									 m_rotation, m_frames[frameNum].origin, m_scale, m_spriteEffects);

}
