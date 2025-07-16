#pragma once

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

class IMenuSystemInteraction
{
public:
	virtual ~IMenuSystemInteraction() {}
	virtual void OnConfirmPressed(int selectedIndex) = 0;
	virtual void OnCancelPressed() = 0;
	virtual bool IsMenuItemSelectionAllowed(Vector2 direction, int index) = 0;
};