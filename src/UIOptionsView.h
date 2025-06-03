#pragma once

#include "IMenuSystemInteraction.h"
#include "UIView.h"

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

	virtual void OnConfirmPressed(int selectedIndex) override;
	virtual void OnCancelPressed() override;
	virtual bool IsMenuItemSelectionAllowed(Vector2 direction, int index) override;
	virtual void HandleMenuItemSelection(int index) override;
};