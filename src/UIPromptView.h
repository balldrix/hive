#pragma once

#include "UIMenuView.h"

#include <string>

class Input;
class Graphics;
class UIPanelContainer;
class UISpriteText;

class UIPromptView : public UIMenuView
{
public:
	enum class PromptType
	{
		QuitToMenu,
		QuitToDesktop
	};

	UIPromptView();
	~UIPromptView();

	void Init(std::string name, UIMenuView* parent, Input* input);
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

	void OnCancelPressed() override;

	void SetMessage(std::string message);
	void SetType(PromptType promptType);

	PromptType GetType() const { return m_promptType; }
	UIMenuView* GetParent() const { return m_parent; }

protected:
	void DoTransition(float deltaTime) override;

private:
	static void OnConfirm(UIMenuView* owner);
	static void OnCancel(UIMenuView* owner);

	UIPanelContainer* m_panelContainer;
	UISpriteText* m_message;
	PromptType m_promptType;
	UIMenuView* m_parent;

	void(*onCancel)(UIMenuView* owner);
};