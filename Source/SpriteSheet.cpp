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

	// iterate through sourceRect data and store it in list
	for(json::iterator it = frames.begin(); it != frames.end(); ++it) 
	{
		// get current iterator
		json frame = it.value();

		// data struct
		SpriteFrame spriteFrame;

		// get sourceRect source rect
		json rect = frame["frame"];
		spriteFrame.sourceRect.left = rect["x"];
		spriteFrame.sourceRect.top = rect["y"];
		spriteFrame.sourceRect.right = spriteFrame.sourceRect.left + rect["w"];
		spriteFrame.sourceRect.bottom = spriteFrame.sourceRect.top + rect["h"];

		// rotation
		spriteFrame.rotated = frame["rotated"];
		
		// size
		json size = frame["sourceSize"];
		spriteFrame.size.x = size["w"];
		spriteFrame.size.y = size["h"];

		// calculate origin
		spriteFrame.origin.x = spriteFrame.sourceRect.left + (spriteFrame.size.x * 0.5);
		spriteFrame.origin.y = spriteFrame.sourceRect.top + (spriteFrame.size.y * 0.5);

		// push data into sourceRect list
		m_frames.push_back(spriteFrame);
	}
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
