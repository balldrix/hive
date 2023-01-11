#include "SpriteSheet.h"
#include "Texture.h"
#include "Graphics.h"

Spritesheet::Spritesheet()
{
	m_frames.clear();
}

Spritesheet::~Spritesheet()
{
	m_frames.clear();
}

void Spritesheet::Init(Texture* texture, const std::string &fileName)
{
	// init sprite sheet as one big sprite
	Sprite::Init(texture);

	// read file
	std::ifstream file(fileName);

	// parse data from file
	json data = json::parse(file);

	// get frames data
	json frames = data["frames"];

	m_frames = frames.get<std::vector<SpriteFrameData>>();
	m_origin.x = data.at("meta").at("origin").at("x");
	m_origin.y = data.at("meta").at("origin").at("y");
}

void Spritesheet::Render(Graphics* graphics, int frameNum)
{
	graphics->GetSpriteBatch()->Draw(m_texture->GetTexture(), m_position, &m_frames[frameNum].frame, m_colour,
									 m_rotation, OffsetOrigin(frameNum), m_scale, m_spriteEffects, m_depth);
}

void Spritesheet::Render(Graphics* graphics, Vector2 position, int frameNum)
{
	graphics->GetSpriteBatch()->Draw(m_texture->GetTexture(), position, &m_frames[frameNum].frame, m_colour,
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
