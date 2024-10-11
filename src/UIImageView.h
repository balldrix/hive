#pragma once

#include "UIView.h"
#include "Sprite.h"

class UIImageView : public UIView
{
public:
	UIImageView();
	virtual ~UIImageView() {};
protected:
	Sprite* m_sprite;
};