#pragma once

#include "Texture.h"

class Graphics;

class PixelTexture : public Texture
{
public:
	PixelTexture() {};
	~PixelTexture() = default;

	void Init(Graphics* graphics);
	void Release() override;
};