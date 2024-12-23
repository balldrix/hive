#pragma once

#include "UIView.h"

#include <string>

class UIImageView;

class UIScreenFlashFX : public UIView {
private: 
	const float FlashDuration = 0.4f;
public:
	UIScreenFlashFX();
	~UIScreenFlashFX();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	
	void TransitionIn(bool isAnimating) override;

	void Shutdown() override;

private:
	UIImageView* m_fullscreenImage;
	float m_timer;
};
