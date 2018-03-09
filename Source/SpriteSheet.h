// SpriteSheet.h
// Christopher Ball 2018
// loads sprite sheet data from json file
// and uses it to render frames

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include "pch.h"
#include "Sprite.h"

// sprite sourceRect data
namespace
{
	struct SpriteFrame
	{
		RECT	sourceRect;
		bool	rotated;
		Vector2	size;
		Vector2	origin;
	};

	void from_json(const json& j, SpriteFrame& s)
	{
		json rect = j["frame"];
		s.sourceRect.left = rect["x"];
		s.sourceRect.top = rect["y"];
		s.sourceRect.right = s.sourceRect.left + rect["w"];
		s.sourceRect.bottom = s.sourceRect.top + rect["h"];

		// rotation
		s.rotated = j["rotated"];
		
		// size
		json size = j["sourceSize"];
		s.size.x = size["w"];
		s.size.y = size["h"];

		// calculate origin
		s.origin.x = s.size.x * 0.5f;
		s.origin.y = s.size.y * 0.5f;
	}
}

class SpriteSheet : public Sprite
{
public:
	SpriteSheet();
	~SpriteSheet();
	void Init(Texture* texture, std::string fileName);
	void Render(Graphics* graphics, int frameNum);
	void Render(Graphics* graphics, Vector2 position, int frameNum);

private:
    std::vector<SpriteFrame> m_frames; // list of sprite sheet sourceRect data
};

#endif // !_SPRITESHEET_H_
