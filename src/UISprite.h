#pragma once

#include "Sprite.h"

class Graphics;

class UISprite : public Sprite 
{
public:
	UISprite() {};
	virtual ~UISprite() = default;

	void Render(Graphics* graphics) override;
};
