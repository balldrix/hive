#include "UIMainMenuView.h"

#include "Logger.h"
#include "UITextMenuItemView.h"
#include <DirectXColors.h>
#include "GlobalConstants.h"
#include "Frame.h"
#include "UIStackingView.h"

using namespace GlobalConstants;

static const float TransitionDuration = 1.2f;

UIIMainMenuView::~UIIMainMenuView()
{
	Shutdown();
}

void UIIMainMenuView::Init(std::string name)
{
	m_uiStackingView.Init("Main Menu Stacking View");
	m_uiStackingView.SetHeight(20);
	m_uiStackingView.SetWidth((int)(GameWidth / 2.0f));

	for (size_t i = 0; i < m_menuItems->length(); i++)
	{
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(m_menuItems[i]);
		item->SetText(m_menuItems[i]);
		item->SetSelectedStateColours(Colors::Red.v, Colors::White.v, Colors::Black.v);
		m_uiStackingView.AddView(item);
	}

	Frame frame;
	frame.x = 10;
	frame.y = 40;
	frame.width = (int)(GameWidth / 2.0f);
	frame.height = GameHeight;

	m_uiStackingView.UpdateLayout(frame);
}

void UIIMainMenuView::Update(float deltaTime)
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

void UIIMainMenuView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_uiStackingView.Render(graphics);
}

void UIIMainMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Main Menu View");
}

void UIIMainMenuView::TransitionIn(bool isAnimated)
{
	m_isActive = true;
	m_currentViewState = ViewStates::AnimatingIn;
}

void UIIMainMenuView::TransitionOut(bool isAnimated)
{
	m_currentViewState = ViewStates::AnimatingOut;
}

void UIIMainMenuView::DoTransition(float deltaTime)
{
	if (m_transitionTimer > 0)
	{
		float t = m_transitionTimer / TransitionDuration;
		float lerpedAlpha = std::lerp(1.0f, 0.0f, 1 - t);
		
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
