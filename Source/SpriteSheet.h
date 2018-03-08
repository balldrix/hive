// SpriteSheet.h
// Christopher Ball 2018
// loads sprite sheet data from json file
// and uses it to render frames

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include "pch.h"
#include "Sprite.h"

class SpriteSheet : public Sprite
{
public:
	// sprite sourceRect data
    struct SpriteFrame
    {
        RECT	sourceRect;
		bool	rotated;
		Vector2	size;
        Vector2	origin;
    };

	SpriteSheet();
	~SpriteSheet();
	void Init(Texture* texture, std::string fileName);
	void Render(Graphics* graphics, int frameNum);
	void Render(Graphics* graphics, Vector2 position, int frameNum);

private:
    std::vector<SpriteFrame> m_frames; // list of sprite sheet sourceRect data
};

#endif // !_SPRITESHEET_H_
