#pragma once

#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

class Graphics;
class Texture;
class UIImageView;

class UIBarView :public UIView
{
public:
	UIBarView();
	~UIBarView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	void Shutdown();

	void SetBackgroundTexture(Texture* texture);
	void SetFillTexture(Texture* texture);
	void SetFrameTexture(Texture* texture);

	void SetCurrentValue(const int& value);
	void SetMaxValue(const int& value);
	void SetPosition(const Vector2& position);
	void SetWidth(const unsigned int& value);
	void SetBackgroundColour(Color colour);

private:
	int	m_currentValue;
	int	m_maxValue;
	unsigned int m_width;

	UIImageView* m_backgroundImage;
	UIImageView* m_fillImage;
	UIImageView* m_frameImage;
};