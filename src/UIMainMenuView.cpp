#include "UIMainMenuView.h"

#include "Logger.h"
#include "UITextMenuItemView.h"
#include <DirectXColors.h>
#include "GlobalConstants.h"
#include "Frame.h"
#include "UIStackingView.h"
#include "UIManager.h"

using namespace GlobalConstants;

static const float TransitionDuration = 1.2f;

UIMainMenuView::UIMainMenuView() :
	m_startingAlpha(0.0f),
	m_targetAlpha(0.0f)
{
}

UIMainMenuView::~UIMainMenuView()
{
	Shutdown();
}

void UIMainMenuView::Init(std::string name)
{
	m_uiStackingView.Init("Main Menu Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	int size = sizeof(m_menuItems) / sizeof(std::string);

	for (size_t i = 0; i < size; i++)
	{
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(m_menuItems[i]);
		item->SetText(m_menuItems[i]);
		item->SetSelectedStateColours(Colors::Red.v, Colors::White.v, Colors::Black.v);
		m_uiStackingView.AddView(item);
	}

	Frame frame{};
	frame.x = 20;
	frame.y = 40;
	frame.width = (int)(GameWidth / 2.0f);
	frame.height = GameHeight;

	m_uiStackingView.UpdateLayout(frame);

	UIManager::RegisterUIView(this);
}

void UIMainMenuView::Update(float deltaTime)
{
	if (!m_isActive) return;

	switch (m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		m_uiStackingView.SetActive(false);
		m_isActive = false;
		m_isAnimating = false;
		break;
	case UIView::ViewStates::AnimatingIn:
		DoTransition(deltaTime);
		break;
	case UIView::ViewStates::Visible:
		m_isAnimating = false;
		break;
	case UIView::ViewStates::AnimatingOut:
		DoTransition(deltaTime);
		break;
	default:
		break;
	}
}

void UIMainMenuView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_uiStackingView.Render(graphics);
}

void UIMainMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Main Menu View");
}

void UIMainMenuView::TransitionIn(bool isAnimated)
{
	m_isActive = true;
	m_uiStackingView.SetActive(true);
	m_currentViewState = ViewStates::AnimatingIn;
	m_transitionTimer = TransitionDuration;
	m_startingAlpha = 0.0f;
	m_targetAlpha = 1.0f;
}

void UIMainMenuView::TransitionOut(bool isAnimated)
{
	m_currentViewState = ViewStates::AnimatingOut;
	m_transitionTimer = TransitionDuration;
	m_startingAlpha = 0.0f;
	m_targetAlpha = 1.0f;
}

void UIMainMenuView::DoTransition(float deltaTime)
{
	if (m_transitionTimer > 0)
	{
		float t = m_transitionTimer / TransitionDuration;
		float lerpedAlpha = std::lerp(m_startingAlpha, m_targetAlpha, 1 - t);
		
		for(UIView* uiView : m_uiStackingView.GetViews())
		{
			Color colour = uiView->GetColour();
			colour.A(lerpedAlpha);
			uiView->SetColour(colour);
		}
		
		m_transitionTimer -= deltaTime;		
		return;
	}

	switch (m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		break;
	case UIView::ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
		break;
	case UIView::ViewStates::Visible:
		break;
	case UIView::ViewStates::AnimatingOut:
		m_currentViewState = ViewStates::NotVisible;
		break;
	default:
		break;
	}
}
