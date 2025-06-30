#pragma once

#include "IMenuSystemInteraction.h"
#include "UIStackingView.h"
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

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

	void OnConfirmPressed(int selectedIndex) override;
	void OnCancelPressed() override;
	bool IsMenuItemSelectionAllowed(Vector2 direction, int index) override;
	void HandleMenuItemSelection(int index) override;

protected:
	void DoTransition(float deltaTime) override;

private:
	static constexpr int MaxOptions = 3;

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

	static void SetSFXVolume(float value);
	void SetMusicVolume();
	void Back();

	MenuOption m_menuOptions[MaxOptions] =
	{
		{ "SFX Volume", OptionType::Slider },
		{ "Music Volume", OptionType::Slider },
		{ "Back", OptionType::Normal, &UIOptionsView::Back }
	};

	UIStackingView m_uiStackingView;
};