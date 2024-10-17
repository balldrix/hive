#pragma once

#include "UIView.h"

class Graphics;
class Sprite;

class UIImageView : public UIView
{
public:
	UIImageView();
	virtual ~UIImageView();
	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	Sprite* GetSprite() const { return m_sprite; }

	void Shutdown();
protected:
	Sprite* m_sprite;
};