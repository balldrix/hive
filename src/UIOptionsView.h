#pragma once

#include "UIMenuView.h"

#include <string>
#include <vector>

class GameStateManager;
class Graphics;
class Input;
class UIPanelContainer;
class Window;

class UIOptionsView : public UIMenuView
{
public:
	UIOptionsView();
	virtual ~UIOptionsView();

	void Init(std::string name, Window* window, Graphics* graphics, Input* input);
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

	void OnCancelPressed() override;

protected:
	void DoTransition(float deltaTime) override;

private:
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

	struct OptionsMenuOption : public MenuOptionBase
	{
		OptionType optionType;
		SelectionType selectionType;
		void(*onIndexChange)(UIMenuView*, int) = nullptr;
		int(*getDefaultValue)(UIMenuView* owner) = nullptr;

		OptionsMenuOption(
			const std::string& label,
			void(*onConfirm)(),
			OptionType optionType,
			SelectionType selectionType,
			void(*onIndexChange)(UIMenuView*, int),
			int(*getDefaultValue)(UIMenuView*)) : MenuOptionBase(label, onConfirm)
		{
			this->optionType = optionType;
			this->selectionType = selectionType;
			this->onIndexChange = onIndexChange;
			this->getDefaultValue = getDefaultValue;
		}
	};

	static void SetSFXVolume(UIMenuView* owner, int index);
	static void SetMusicVolume(UIMenuView* owner, int index);
	static void SetScreenResolution(UIMenuView* owner, int index);
	static void SetFullscreen(UIMenuView* owner, int index);

	static int GetSFXVolumeIndex(UIMenuView* owner);
	static int GetMusicVolumeIndex(UIMenuView* owner);
	static int GetScreenResolutionIndex(UIMenuView* owner);
	static int GetFullscreenIndex(UIMenuView* owner);

	static void Back();

	std::vector<std::string> GetOptionsForOptionType(OptionType optionType);

	UIPanelContainer* m_panelContainer;
};