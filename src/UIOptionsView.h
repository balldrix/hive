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
	static constexpr int MaxOptions = 5;

	enum class OptionType {
		Normal,
		Cycle,
		Slider
	};

	struct MenuOption
	{
		std::string name;
		OptionType type;
		void(*onIndexChange)(int) = nullptr;
		void(*onConfirm)() = nullptr;
		int(*getDefaultValue)() = nullptr;
	};

	static void SetSFXVolume(int index);
	static void SetMusicVolume(int index);
	static void SetScreenResolution(int index);
	static void SetFullscreen(int index);

	static int GetSFXVolumeIndex();
	static int GetMusicVolumeIndex();
	static int GetScreenResolutionIndex();
	static int GetFullscreenIndex();

	static void Back();

	MenuOption m_menuOptions[MaxOptions] =
	{
		{ "SFX Volume", OptionType::Slider, SetSFXVolume, nullptr, GetSFXVolumeIndex },
		{ "Music Volume", OptionType::Slider, SetMusicVolume, nullptr, GetMusicVolumeIndex },
		{ "Resolution", OptionType::Cycle, SetScreenResolution, nullptr, GetScreenResolutionIndex },
		{ "Fullscreen", OptionType::Cycle, SetFullscreen, nullptr, GetFullscreenIndex },
		{ "Back", OptionType::Normal, nullptr, Back, nullptr }
	};

	Vector2 m_resolutions[3] =
	{
		Vector2(1024, 576),
		Vector2(1280, 720),
		Vector2(1960, 1080)
	};

	std::string m_fullscreenModes[2] =
	{
		"fullscreen",
		"windowed"
	};

	UIStackingView m_uiStackingView;
};