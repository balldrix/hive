#include "UIOptionsView.h"

#include <directxtk/SimpleMath.h>
#include "Graphics.h"
#include <string>

UIOptionsView::UIOptionsView()
{
}

UIOptionsView::~UIOptionsView()
{
}

void UIOptionsView::Init(std::string name)
{
}

void UIOptionsView::Update(float deltaTime)
{
}

void UIOptionsView::Render(Graphics* graphics)
{
}

void UIOptionsView::Shutdown()
{
}

void UIOptionsView::OnConfirmPressed(int selectedIndex)
{
}

void UIOptionsView::OnCancelPressed()
{
}

bool UIOptionsView::IsMenuItemSelectionAllowed(Vector2 direction, int index)
{
	return false;
}

void UIOptionsView::HandleMenuItemSelection(int index)
{
}
