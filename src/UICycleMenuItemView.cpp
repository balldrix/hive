#include "UICycleMenuItemView.h"

UICycleMenuItemView::UICycleMenuItemView() :
	m_currentIndex(0),
	m_options(),
	m_repeatTimer(0.0f),
	m_leftArrow(nullptr),
	m_rightArrow(nullptr),
	m_optionText(nullptr)
{
}

UICycleMenuItemView::~UICycleMenuItemView()
{
}

void UICycleMenuItemView::Init(std::string name, std::vector<std::string> options, int defaultIndex, void(*delegate)(int))
{
}

void UICycleMenuItemView::SetPosition(const Vector2& position)
{
}

void UICycleMenuItemView::SetColour(Color colour)
{
}

void UICycleMenuItemView::Update(float deltaTime)
{
}

void UICycleMenuItemView::Render(Graphics* graphics)
{
}

void UICycleMenuItemView::SelectNextOption()
{
}

void UICycleMenuItemView::SelectPreviousOption()
{
}

void UICycleMenuItemView::HandleOptionChange(int index)
{
}
