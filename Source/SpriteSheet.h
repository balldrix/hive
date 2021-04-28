#pragma once

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
    std::vector<SpriteFrameData> m_frames; 
};