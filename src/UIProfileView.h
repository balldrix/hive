#pragma once

#include "UIView.h"

#include <string>

class Graphics;
class UIImageView;

class UIProfileView : public UIView
{
public:
	UIProfileView();
	~UIProfileView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	void Shutdown() override;

private:
	UIImageView* m_frame;
	UIImageView* m_characterImage;
};