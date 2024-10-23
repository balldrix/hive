#pragma once

#include "UIMenuItemView.h"
#include "UISpriteText.h"
#include <directxtk/SimpleMath.h>

using namespace DirectX;
using namespace SimpleMath;

class UITextMenuItemView : public UIMenuItemView
{
public:
	UITextMenuItemView();
	~UITextMenuItemView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void SetActive(bool isActive) override;

	int GetHeight() const override { return m_uiSpriteText->GetHeight(); }
	int GetWidth() const override { return m_uiSpriteText->GetWidth(); }
	Color GetColour() const { return m_uiSpriteText->GetColour(); }

	void SetText(std::string text);
	void SetSelectedStateColours(Color selected, Color unselected, Color disabled);
	void SetPosition(const Vector2& position);
	void SetColour(Color colour);

private:
	UISpriteText* m_uiSpriteText;
	Color m_selectedTextColour;
	Color m_unselectedTextColour;
	Color m_disabledTextColour;
};