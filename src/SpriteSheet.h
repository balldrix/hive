#pragma once

#include "Sprite.h"
#include "SpriteFrameData.h"

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class Graphics;
class Texture;

class Spritesheet : public Sprite
{
public:
	Spritesheet();
	~Spritesheet();
	void Init(Texture* texture, std::vector<SpriteFrameData> spriteFrameData);
	void Render(Graphics* graphics, int frameNum);
	void Render(Graphics* graphics, Vector2 position, int frameNum);
	SpriteFrameData GetFrameData(int index) const { return m_frames.at(index); }

private:
	Vector2 OffsetOrigin(unsigned int frameNum);
    std::vector<SpriteFrameData> m_frames; 
};