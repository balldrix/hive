#include "UISliderMenuItemView.h"

#include "AssetLoader.h"
#include "Graphics.h"
#include "UIBarView.h"
#include "UIMenuItemView.h"
#include "UITextMenuItemView.h"

#include <algorithm>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

UISliderMenuItemView::UISliderMenuItemView() :
	m_sliderBar(nullptr),
	m_labelText(nullptr),
	m_maxValue(0.0f)
{
}

UISliderMenuItemView::~UISliderMenuItemView()
{
	Shutdown();
}

void UISliderMenuItemView::Init(std::string name, float max, int defaultValue, Color colour, void (*delegate)(int))
{
	m_maxValue = max;
	m_selectedIndex = defaultValue;

	m_labelText = new UITextMenuItemView();
	m_labelText->Init(name);
	m_labelText->SetText(name);

	m_sliderBar = new UIBarView();
	m_sliderBar->Init(fmt::format("{0}_slider", name));
	m_sliderBar->SetCurrentValue(defaultValue / SliderScaler);
	m_sliderBar->SetMaxValue(max);
	m_sliderBar->SetFillTexture(AssetLoader::GetTexture("t_pixel"));
	m_sliderBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_sliderBar->SetBackgroundColour(Colors::SlateGray.v);
	m_sliderBar->SetWidth(100);
	m_sliderBar->SetHeight(GetHeight());
	m_sliderBar->SetActive(true);
	m_sliderBar->SetDepth(0.5f);
	onSliderChanged = delegate;
}

void UISliderMenuItemView::Update(float deltaTime)
{
	if(!m_isActive) return;

	m_sliderBar->Update(deltaTime);
	UIMenuItemView::Update(deltaTime);
}

void UISliderMenuItemView::SetActive(bool isActive)
{
	m_isActive = isActive;
	m_labelText->SetActive(isActive);
	m_sliderBar->SetActive(isActive);
}

void UISliderMenuItemView::SetPosition(const Vector2& position)
{
	m_labelText->SetPosition(position);
	m_sliderBar->SetPosition(Vector2(104.0f, position.y));
}

void UISliderMenuItemView::SetColour(Color colour)
{
	m_labelText->SetColour(colour);
	m_sliderBar->SetColour(colour);
}

void UISliderMenuItemView::SetAlpha(float alpha)
{
	m_labelText->SetAlpha(alpha);
	m_sliderBar->SetAlpha(alpha);
}

void UISliderMenuItemView::Render(Graphics* graphics)
{
	m_labelText->Render(graphics);
	m_sliderBar->Render(graphics);
}

void UISliderMenuItemView::HandleOptionChange(int index)
{
	m_selectedIndex = std::clamp(index, 0, (int)(m_maxValue * SliderScaler));
	m_sliderBar->SetCurrentValue(m_maxValue / SliderScaler * m_selectedIndex);

	if(onSliderChanged) onSliderChanged(index);
}

void UISliderMenuItemView::HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState)
{
	auto it = m_selectionStateColours.find(newSelectionState);
	if(it != m_selectionStateColours.end())
	{
		m_labelText->SetColour(it->second);
	}
}

void UISliderMenuItemView::Shutdown()
{
	delete m_sliderBar;
	m_sliderBar = nullptr;

	delete m_labelText;
	m_labelText = nullptr;
}