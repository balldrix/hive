#pragma once

#include "IMenuSystemInteraction.h"
#include "UIStackingView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

class GameStateManager;
class Graphics;
class Window;

class UIMenuView : public UIView, public IMenuSystemInteraction
{
public:
	UIMenuView();
	virtual ~UIMenuView() {};

	virtual void Update(float deltaTime) override;
	virtual void Render(Graphics* graphics) override;
	virtual void Shutdown() override;

	virtual void TransitionIn(bool isAnimated) override;
	virtual void TransitionOut(bool isAnimated) override;

	virtual void OnConfirmPressed(int selectedIndex) override;
	virtual void OnCancelPressed() override {};
	virtual bool IsMenuItemSelectionAllowed(Vector2 direction, int index) override;

	Window* GetWindow() const { return m_window; }
	Graphics* GetGraphics() const { return m_graphics; }

	struct MenuOptionBase {
		std::string label;
		MenuOptionBase(const std::string& label, void(*onConfirm)())
		{
			this->label = label;
			this->onConfirm = onConfirm;
		}

		virtual ~MenuOptionBase() = default;
		void(*onConfirm)() = nullptr;

		void OnConfirm() const {
			if(onConfirm) onConfirm();
		}
	};

protected:
	virtual void DoTransition(float deltaTime) override;

	UIStackingView m_uiStackingView;
	std::vector<MenuOptionBase*> m_menuOptions;
	float m_lerpedAlpha;

	Window* m_window;
	Graphics* m_graphics;
};