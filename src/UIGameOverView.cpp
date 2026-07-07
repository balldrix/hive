#include "UIGameOverView.h"

#include "AssetLoader.h"
#include "Frame.h"
#include "GameStateNameLibrary.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Input.h"
#include "LoadingGameState.h"
#include "Logger.h"
#include "UIImageView.h"
#include "UIManager.h"
#include "UIMenuView.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"
#include "UIMenuItemView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX;
using namespace GameStateNameLibrary;
using namespace GlobalConstants;

UIGameOverView::UIGameOverView() :
	m_backgroundImage(nullptr)
{

}

UIGameOverView::~UIGameOverView()
{
	Shutdown();
}

void UIGameOverView::Init(std::string name, Input* input)
{
	m_name = name;

	Logger::LogInfo("Initialising UI Game Over View.");

	m_backgroundImage = new UIImageView();
	m_backgroundImage->Init("UI Image View", AssetLoader::GetTexture("t_gameover_bg"));
	m_backgroundImage->TransitionOut(false);

	auto sprite = m_backgroundImage->GetSprite();
	sprite->SetOrigin(Vector2::Zero);

	m_uiStackingView.Init("Game Over Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	m_menuOptions.emplace_back(new MenuOptionBase("Retry", Retry));
	m_menuOptions.emplace_back(new MenuOptionBase("Wishlist", Retry));
	m_menuOptions.emplace_back(new MenuOptionBase("Quit", Quit));

	for(const auto& option : m_menuOptions)
	{
		std::string name = option->label;
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(name, input);
		item->SetText(name);
		item->SetSelectedStateColours(Colors::White.v, Colors::SlateGray.v, Colors::Black.v);
		item->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
		m_uiStackingView.AddView(item);
	}

	SetupNavigation();

	Frame frame{};
	frame.x = 20;
	frame.y = 40;
	frame.width = (int)(GameWidth / 2.0f);
	frame.height = GameHeight;

	m_uiStackingView.UpdateLayout(frame);

	m_assignedStates.push_back(GameOver);

	UIManager::RegisterUIView(this);
}

void UIGameOverView::Render(Graphics* graphics)
{
	if(m_isActive == false) return;

	m_backgroundImage->Render(graphics);
	UIMenuView::Render(graphics);
}

void UIGameOverView::Shutdown()
{
	Logger::LogInfo("Shutting down UI GameOver View.");

	UIManager::UnregisterUIView(this);

	delete m_backgroundImage;
	m_backgroundImage = nullptr;
}

void UIGameOverView::TransitionIn(bool isAnimating)
{
	UIMenuView::TransitionIn(isAnimating);
	m_backgroundImage->TransitionIn(isAnimating);
}

void UIGameOverView::Retry(UIMenuView* owner)
{
	LoadingGameState::ProceedToGameplay();
}

void UIGameOverView::Quit(UIMenuView* owner)
{
	LoadingGameState::s_isloadingFromMainGameplayToFrontend = true;
	LoadingGameState::ProceedToFrontEnd();
}

void UIGameOverView::Wishlist(UIMenuView* owner)
{
}
