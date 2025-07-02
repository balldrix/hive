#pragma once

#include "AudioEngine.h"
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
		void(*onIndexChange)(float) = nullptr;
		void(*onConfirm)() = nullptr;
		float(*getDefaultValue)() = nullptr;
	};

	static void SetSFXVolume(float value);
	static void SetMusicVolume(float value);
	static void Back();

	MenuOption m_menuOptions[MaxOptions] =
	{
		{ "SFX Volume", OptionType::Slider, SetSFXVolume, nullptr, []() { return AudioEngine::Instance()->GetSFXVolume(); }},
		{ "Music Volume", OptionType::Slider, SetMusicVolume, nullptr, []() { return AudioEngine::Instance()->GetMusicVolume(); }},
		{ "Back", OptionType::Normal, nullptr, Back, nullptr }
	};

	UIStackingView m_uiStackingView;
};