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
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>
#include <Windows.h>

using namespace DirectX;
using namespace GameStateNameLibrary;
using namespace GlobalConstants;

UIGameOverView::UIGameOverView() :
	m_backgroundImage(nullptr),
	m_overlayImage(nullptr),
	m_gameOverTitle(nullptr)
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
	m_backgroundImage->Init("Background", AssetLoader::GetTexture("t_gameover_bg"));
	m_backgroundImage->TransitionOut(false);

	auto sprite = m_backgroundImage->GetSprite();
	sprite->SetOrigin(Vector2::Zero);

	m_overlayImage = new UIImageView();
	m_overlayImage->Init("Overlay", AssetLoader::GetTexture("t_pixel"), Vector2::Zero);

	RECT overlayRect{};
	overlayRect.left = 0;
	overlayRect.top = 0;
	overlayRect.right = GameWidth;
	overlayRect.bottom = GameHeight;

	sprite = m_overlayImage->GetSprite();
	sprite->SetSourceRect(overlayRect);
	sprite->SetColour(DirectX::Colors::Black.v);
	sprite->SetAlpha(0.2f);
	sprite->SetDepth(0.25f);
	m_overlayImage->TransitionOut(false);

	m_uiStackingView.Init("Game Over Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Horizontal);

	m_menuOptions.emplace_back(new MenuOptionBase("Retry", Retry));
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

	int totalWidth = 0;
	auto menuItems = m_uiStackingView.GetMenuItems();

	for(auto* item : menuItems)
	{
		totalWidth += item->GetWidth();
	}

	const int spacing = 8;
	m_uiStackingView.SetSpacing(spacing);

	if(menuItems.size() > 1)
	{
		totalWidth += spacing * ((int)menuItems.size() - 1);
	}

	Frame frame{};
	frame.x = (GameWidth - totalWidth) / 2;
	frame.y = 120;
	frame.width = totalWidth;
	frame.height = GameHeight;

	m_uiStackingView.UpdateLayout(frame);

	m_assignedStates.push_back(GameOver);

	UIManager::RegisterUIView(this);
}

void UIGameOverView::Render(Graphics* graphics)
{
	if(m_isActive == false) return;

	m_backgroundImage->Render(graphics);
	m_overlayImage->Render(graphics);
	UIMenuView::Render(graphics);
}

void UIGameOverView::Shutdown()
{
	Logger::LogInfo("Shutting down UI GameOver View.");

	UIManager::UnregisterUIView(this);

	delete m_overlayImage;
	m_overlayImage = nullptr;

	delete m_backgroundImage;
	m_backgroundImage = nullptr;
}

void UIGameOverView::TransitionIn(bool isAnimating)
{
	UIMenuView::TransitionIn(isAnimating);
	m_backgroundImage->TransitionIn(isAnimating);
	m_overlayImage->TransitionIn(isAnimating);
}

void UIGameOverView::SetupNavigation()
{
	auto options = m_uiStackingView.GetMenuItems();

	for(int i = 0; i < options.size(); i++)
	{
		int left = i == 0 ? -1 : i - 1;
		int right = i + 1;

		if(i == options.size() - 1)
		{
			right = -1;
		}

		UIMenuItemView::Navigation nav;
		nav.up = -1;
		nav.down = -1;
		nav.left = left;
		nav.right = right;

		options[i]->SetNavigation(nav);
	}
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
