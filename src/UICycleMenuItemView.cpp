#include "UICycleMenuItemView.h"

#include "AssetLoader.h"
#include "Graphics.h"
#include "Input.h"
#include "UIConfig.h"
#include "UIImageView.h"
#include "UIMenuItemView.h"
#include "UISpriteText.h"
#include "UITextMenuItemView.h"

#include <DirectXMath.h>
#include <DirectXMathVector.inl>
#include <directxtk/SimpleMath.h>
#include <directxtk/SpriteFont.h>
#include <string>
#include <vector>

UICycleMenuItemView::UICycleMenuItemView() :
	m_currentIndex(0),
	m_options(),
	m_repeatTimer(0.0f),
	m_labelText(nullptr),
	m_leftArrow(nullptr),
	m_rightArrow(nullptr),
	m_optionText(nullptr),
	onOptionChanged(nullptr)
{
}

UICycleMenuItemView::~UICycleMenuItemView()
{
	Shutdown();
}

void UICycleMenuItemView::Init(std::string name, Input* input, std::vector<std::string> options, int defaultIndex, void(*delegate)(UIMenuView* owner, int), UIMenuView* owner)
{
	m_input = input;
	m_owner = owner;
	m_labelText = new UITextMenuItemView();
	m_labelText ->Init(name, input);
	m_labelText ->SetText(name);

	m_options = options;
	onOptionChanged = delegate;
	m_selectedIndex = defaultIndex;

	m_leftArrow = new UIImageView();
	m_leftArrow->Init("Left Arrow", AssetLoader::GetTexture("t_arrow"));
	m_leftArrow->SetFlipped(true);
	m_leftArrow->SetOrigin(Vector2::Zero);
	m_leftArrow->SetDepth(0.5f);

	m_rightArrow = new UIImageView();
	m_rightArrow->Init("Right Arrow", AssetLoader::GetTexture("t_arrow"));
	m_rightArrow->SetOrigin(Vector2::Zero);
	m_rightArrow->SetDepth(0.5f);

	m_optionText = new UISpriteText();
	m_optionText->Init(UIConfig::DespairFont8);
	m_optionText->SetDepth(0.5f);
	m_optionText->SetText(m_options[m_selectedIndex]);
	m_optionText->SetAlignment(UISpriteText::Alignments::Centre);
}

int UICycleMenuItemView::GetWidth() const
{
	int width;
	int maxTextWidth = 0;

	for(const auto& it : m_options)
	{
		XMVECTOR measure = m_labelText->GetSpriteFont()->MeasureString(it.c_str());
		int textWidth = (int)XMVectorGetX(measure);
		if(maxTextWidth > textWidth) continue;

		maxTextWidth = textWidth;
	}

	width = m_labelText->GetWidth() + m_leftArrow->GetWidth() + m_rightArrow->GetWidth() + maxTextWidth;

	return width;
}

void UICycleMenuItemView::SetActive(bool isActive)
{
	m_isActive = isActive;
	m_labelText->SetActive(isActive);
	m_leftArrow->SetActive(isActive);
	m_rightArrow->SetActive(isActive);
	m_optionText->SetActive(isActive);
}

void UICycleMenuItemView::SetPosition(const Vector2& position)
{
	m_labelText->SetPosition(position);
	m_leftArrow->SetPosition(Vector2(100, position.y));
	m_rightArrow->SetPosition(Vector2(200, position.y));
	m_optionText->SetPosition(Vector2(150, position.y));
};

void UICycleMenuItemView::SetColour(Color colour)
{
	m_labelText->SetColour(colour);
}

void UICycleMenuItemView::SetAlpha(float alpha)
{
	m_labelText->SetAlpha(alpha);
	m_leftArrow->SetAlpha(alpha);
	m_rightArrow->SetAlpha(alpha);

	Color optionColour = m_optionText->GetColour();
	optionColour.A(alpha);
	m_optionText->SetColour(optionColour);
}

void UICycleMenuItemView::Render(Graphics* graphics)
{
	m_optionText->Render(graphics);
	m_labelText->Render(graphics);
	m_leftArrow->Render(graphics);
	m_rightArrow->Render(graphics);
}

void UICycleMenuItemView::Shutdown()
{
	delete m_optionText;
	delete m_rightArrow;
	delete m_leftArrow;
	delete m_labelText;

	m_optionText = nullptr;
	m_rightArrow = nullptr;
	m_leftArrow = nullptr;
	m_labelText = nullptr;
}

void UICycleMenuItemView::HandleOptionChange(int index)
{
	if(index >= static_cast<int>(m_options.size())) 
	{
		m_selectedIndex = 0;
	}
	else if(index < 0)
	{
		m_selectedIndex = static_cast<int>(m_options.size() - 1);
	}

	std::string option = m_options[m_selectedIndex];
	m_optionText->SetText(option);
	m_optionText->SetAlignment(UISpriteText::Alignments::Centre);

	if(onOptionChanged) onOptionChanged(m_owner, m_selectedIndex);
}

void UICycleMenuItemView::HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState)
{
	auto it = m_selectionStateColours.find(newSelectionState);
	if(it != m_selectionStateColours.end())
	{
		m_labelText->SetColour(it->second);
		m_leftArrow->SetColour(it->second);
		m_rightArrow->SetColour(it->second);
		m_optionText->SetColour(it->second);
	}
}
