#pragma once

#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

class Graphics;
class Texture;
class UIImageView;

class UIPortraitView : public UIView
{
public:
	UIPortraitView();
	~UIPortraitView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	void Shutdown() override;

	void SetPortraitTexture(Texture* texture);
	void SetPosition(const Vector2& position);

private:
	UIImageView* m_frame;
	UIImageView* m_characterImage;
};