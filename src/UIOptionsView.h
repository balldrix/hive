#pragma once

#include "UIMenuView.h"

#include <string>
#include <vector>

class Graphics;
class UIPanelContainer;

class UIOptionsView : public UIMenuView
{
public:
	UIOptionsView();
	virtual ~UIOptionsView();

	void Init(std::string name) override;
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
		void(*onIndexChange)(int) = nullptr;
		int(*getDefaultValue)() = nullptr;

		OptionsMenuOption(
			const std::string& label,
			void(*onConfirm)(),
			OptionType optionType,
			SelectionType selectionType,
			void(*onIndexChange)(int),
			int(*getDefaultValue)()) : MenuOptionBase(label, onConfirm)
		{
			this->optionType = optionType;
			this->selectionType = selectionType;
			this->onIndexChange = onIndexChange;
			this->getDefaultValue = getDefaultValue;
		}
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

	UIPanelContainer* m_panelContainer;
};