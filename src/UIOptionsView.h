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

	enum class SelectionType
	{
		Fixed,
		Cycle,
		Slider
	};

	enum class OptionType
	{
		SFXVolume,
		MusicVolume,
		Resolution,
		Fullscreen,
		None
	};

	struct MenuOption
	{
		std::string label;
		OptionType optionType;
		SelectionType selectionType;
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

	std::vector<std::string> GetOptionsForOptionType(OptionType optionType);

	MenuOption m_menuOptions[MaxOptions] =
	{
		{ "SFX Volume", OptionType::SFXVolume, SelectionType::Slider, SetSFXVolume, nullptr, GetSFXVolumeIndex },
		{ "Music Volume", OptionType::MusicVolume, SelectionType::Slider, SetMusicVolume, nullptr, GetMusicVolumeIndex },
		{ "Resolution", OptionType::Resolution, SelectionType::Cycle, SetScreenResolution, nullptr, GetScreenResolutionIndex },
		{ "Fullscreen", OptionType::Fullscreen, SelectionType::Cycle, SetFullscreen, nullptr, GetFullscreenIndex },
		{ "Back", OptionType::None , SelectionType::Fixed, nullptr, Back, nullptr }
	};

	std::string m_fullscreenModes[2] =
	{
		"fullscreen",
		"windowed"
	};

	UIStackingView m_uiStackingView;
};