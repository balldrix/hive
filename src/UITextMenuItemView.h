#pragma once

#include "UIMenuItemView.h"
#include "UISpriteText.h"

#include <directxtk/SimpleMath.h>
#include <directxtk/SpriteFont.h>
#include <string>

using namespace DirectX;
using namespace SimpleMath;

class Graphics;
class Input;

class UITextMenuItemView : public UIMenuItemView
{
public:
	UITextMenuItemView();
	~UITextMenuItemView();

	void Init(std::string name, Input* input);
	void Render(Graphics* graphics) override;
	void Shutdown() override;
	void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) override;

	void SetActive(bool isActive) override;

	int GetHeight() const override { return m_uiSpriteText->GetHeight(); }
	int GetWidth() const override { return m_uiSpriteText->GetWidth(); }
	Color GetColour() override { return m_uiSpriteText->GetColour(); }
	SpriteFont* GetSpriteFont() const { return m_uiSpriteText->GetSpriteFont(); }

	void SetText(std::string text);
	void SetAlignment(UISpriteText::Alignments alignment);
	virtual void SetPosition(const Vector2& position) override;
	virtual void SetColour(Color colour) override;
	virtual void SetAlpha(float alpha) override;
	virtual void SetDepth(float alpha) override;

private:
	UISpriteText* m_uiSpriteText;
};