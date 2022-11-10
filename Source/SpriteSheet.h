#pragma once

#include "pch.h"
#include "Sprite.h"
#include "SpriteFrameData.h"

class Spritesheet : public Sprite
{
public:
	Spritesheet();
	~Spritesheet();
	void Init(Texture* texture, const std::string &fileName);
	void Render(Graphics* graphics, int frameNum);
	void Render(Graphics* graphics, Vector2 position, int frameNum);
	SpriteFrameData GetFrameData(unsigned int index) const { return m_frames[index]; }

private:
	Vector2 OffsetOrigin(unsigned int frameNum);
    std::vector<SpriteFrameData> m_frames; 
};