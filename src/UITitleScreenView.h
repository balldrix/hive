#pragma once

#include "GlobalConstants.h"
#include "UIView.h"

#include <DirectXTK/SimpleMath.h>

using namespace GlobalConstants;
using namespace DirectX;
using namespace SimpleMath;

class UISpriteText;
class UIImageView;

static const float TransitionDuration = 0.4f;
static const Vector2 LogoImageStartPosition = Vector2(GameWidth - 20.0f, 40.0f);
static const Vector2 StartGameTextStartPosition = Vector2(GameWidth / 2.0f, GameHeight - 10.0f);

class UITitleScreenView : public UIView
{
public:
	UITitleScreenView();
	virtual ~UITitleScreenView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void Update(float deltaTime) override;

	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;

	void Shutdown() override;

protected:
	void DoTransition(float deltaTime) override;

private:

	UISpriteText* m_startGameText;
	UIImageView* m_logoImage;
};