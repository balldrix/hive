#include "UICycleMenuItemView.h"

UICycleMenuItemView::UICycleMenuItemView() :
	m_currentIndex(0),
	m_options(),
	m_repeatTimer(0.0f),
	m_leftArrow(nullptr),
	m_rightArrow(nullptr),
	m_optionText(nullptr),
	onOptionChanged(nullptr)
{
}

UICycleMenuItemView::~UICycleMenuItemView()
{
	delete m_optionText;
	delete m_rightArrow;
	delete m_leftArrow;

	m_optionText = nullptr;
	m_rightArrow = nullptr;
	m_leftArrow = nullptr;
}

void UICycleMenuItemView::Init(std::string name, std::vector<std::string> options, int defaultIndex, void(*delegate)(int))
{
	UITextMenuItemView::Init(name);
	UITextMenuItemView::SetText(name);

	m_options = options;
	onOptionChanged = delegate;
	m_selectedIndex = defaultIndex;

	m_leftArrow = new UIImageView();
	m_rightArrow = new UIImageView();
	m_optionText = new UISpriteText();
}

void UICycleMenuItemView::SetPosition(const Vector2& position)
{
	UITextMenuItemView::SetPosition(position);
}

void UICycleMenuItemView::SetColour(Color colour)
{
	UITextMenuItemView::SetColour(colour);
}

void UICycleMenuItemView::Update(float deltaTime)
{
}

void UICycleMenuItemView::Render(Graphics* graphics)
{
	UITextMenuItemView::Render(graphics);
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
