#pragma once

#include "IMenuSystemInteraction.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

class Graphics;

class UIOptionsView : public UIView, IMenuSystemInteraction
{
public:
	UIOptionsView();
	virtual ~UIOptionsView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void OnConfirmPressed(int selectedIndex) override;
	void OnCancelPressed() override;
	bool IsMenuItemSelectionAllowed(Vector2 direction, int index) override;
	void HandleMenuItemSelection(int index) override;

private:
	enum class OptionType {
		Normal,
		Cycle,
		Slider
	};

	struct MenuOption
	{
		std::string name;
		OptionType type;
		void(UIOptionsView::* function)();
	};

	void SetSFXVolume();
	void SetMusicVolume();
	void Back();
};