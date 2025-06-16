#include "UISliderMenuItemView.h"

#include "AssetLoader.h"
#include "UIBarView.h"
#include "UITextMenuItemView.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>
#include "Graphics.h"

UISliderMenuItemView::UISliderMenuItemView() :
	m_sliderBar(nullptr)
{
}

UISliderMenuItemView::~UISliderMenuItemView()
{
	delete m_sliderBar;
	m_sliderBar = nullptr;
}

void UISliderMenuItemView::Init(std::string name, float min, float max, float defaultValue, Color colour)
{
	UITextMenuItemView::Init(name);
	UITextMenuItemView::SetText(name);

	m_sliderBar = new UIBarView();
	m_sliderBar->Init(fmt::format("{}_slider", name));
	m_sliderBar->SetCurrentValue(defaultValue);
	m_sliderBar->SetMaxValue(max);
	m_sliderBar->SetFillTexture(AssetLoader::GetTexture("t_pixel"));
	m_sliderBar->SetWidth(100);
	m_sliderBar->SetHeight(GetHeight());
	m_sliderBar->Update(0.0f);
	m_sliderBar->SetActive(true);
}

void UISliderMenuItemView::SetPosition(const Vector2& position)
{
	UITextMenuItemView::SetPosition(position);
	m_sliderBar->SetPosition(Vector2(GetWidth() + 50.0f, position.y));
}

void UISliderMenuItemView::Render(Graphics* graphics)
{
	UITextMenuItemView::Render(graphics);
	m_sliderBar->Render(graphics);
}
