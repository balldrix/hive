#pragma once

#include "UIView.h"

class Graphics;
class Sprite;

class UIImageView : public UIView
{
public:
	UIImageView();
	virtual ~UIImageView();
	void Init(std::string name);
	void Render(Graphics* graphics);

	Sprite* GetSprite() const { return m_sprite; }

	void Shutdown();
protected:
	Sprite* m_sprite;
};