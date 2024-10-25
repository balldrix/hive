#pragma once

class IMenuSystemInteraction
{
public:
	virtual ~IMenuSystemInteraction() {}
	virtual void OnConfirmPressed(int selectedIndex) = 0;
	virtual void OnCancelPressed() = 0;
	virtual void AllowMenuItemSelection(Vector2 direction, int index) = 0;
	virtual void HandleMenuItemSelection(int index) = 0;
};