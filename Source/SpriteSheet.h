// Spritesheet.h
// Christopher Ball 2019
// loads sprite sheet data from json file
// and uses it to render frames

#ifndef _SPRITESHEET_H_
#define _SPRITESHEET_H_

#include "pch.h"
#include "Sprite.h"
#include "SpriteFrameData.h"

class Spritesheet : public Sprite
{
public:
	Spritesheet();
	~Spritesheet();
	void Init(Texture* texture, std::string fileName);
	void Render(Graphics* graphics, int frameNum);
	void Render(Graphics* graphics, Vector2 position, int frameNum);

private:
    std::vector<SpriteFrameData> m_frames; // list of sprite sheet sourceRect data
};

#endif // !_SPRITESHEET_H_
