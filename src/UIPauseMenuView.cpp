#include "UIPauseMenuView.h"

#include "AssetLoader.h"
#include "Frame.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "UIImageView.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UISpriteText.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace GlobalConstants;

UIPauseMenuView::UIPauseMenuView() :
	m_backgroundOverlayImage(nullptr),
	m_panelImage(nullptr),
	m_titleText(nullptr)
{
}

UIPauseMenuView::~UIPauseMenuView()
{
	Shutdown();
}

void UIPauseMenuView::Init(std::string name)
{
	Logger::LogInfo("Initialising UI Pause Menu View.");

	m_backgroundOverlayImage = new UIImageView();
	m_backgroundOverlayImage->Init("Pause Overlay Image");
	m_backgroundOverlayImage->GetSprite()->Init(AssetLoader::GetTexture("t_pixel"));
	m_backgroundOverlayImage->GetSprite()->SetSourceRect(RECT{ 0, 0, GameWidth, GameHeight });
	m_backgroundOverlayImage->SetAlpha(0.4f);
	m_backgroundOverlayImage->SetOrigin(Vector2::Zero);
	m_backgroundOverlayImage->SetColour(Colors::Black.v);
	m_backgroundOverlayImage->SetDepth(0.9f);

	m_panelImage = new UIImageView();
	m_panelImage->Init("Panel Image");
	m_panelImage->GetSprite()->Init(AssetLoader::GetTexture("t_pixel"));
	m_panelImage->GetSprite()->SetSourceRect(RECT{0, 0, 180, 100});
	m_panelImage->SetOrigin(Vector2(90.0f, 40.0f));
	m_panelImage->SetPosition(Vector2(GameWidth / 2.0f, GameHeight / 2.0f));
	m_panelImage->SetColour(Color(0.17f, 0.18f, 0.2f, 0.9f));
	m_panelImage->SetDepth(0.5f);

	m_name = name;
	m_uiStackingView.Init("Pause Menu Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	m_menuOptions.emplace_back(new MenuOptionBase("Continue", Continue));
	m_menuOptions.emplace_back(new MenuOptionBase("Options", ProceedToOptionsView));
	m_menuOptions.emplace_back(new MenuOptionBase("Quit To Menu", ShowQuitToMenuPrompt));
	m_menuOptions.emplace_back(new MenuOptionBase("Quit To Desktop", ShowQuitToDesktopPrompt));

	for(const auto& option : m_menuOptions)
	{
		std::string name = option->label;
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(name);
		item->SetText(name);
		item->SetSelectedStateColours(Colors::White.v, Colors::SlateGray.v, Colors::Black.v);
		item->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
		m_uiStackingView.AddView(item);
	}

	auto options = m_uiStackingView.GetMenuItems();

	for(int i = 0; i < options.size(); i++)
	{
		int up = i == 0 ? -1 : i - 1;
		int down = i + 1;

		if(i == options.size() - 1)
		{
			down = -1;
		}

		UIMenuItemView::Navigation nav;
		nav.up = up;
		nav.down = down;
		nav.left = -1;
		nav.right = -1;

		options[i]->SetNavigation(nav);
	}

	Frame frame{};
	frame.x = 50;
	frame.y = 60;
	frame.width = (int)(GameWidth / 2.0f);
	frame.height = GameHeight;

	m_uiStackingView.UpdateLayout(frame);

	m_assignedStates.push_back("Paused");

	UIManager::RegisterUIView(this);
}

void UIPauseMenuView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	UIMenuView::Render(graphics);
	m_backgroundOverlayImage->Render(graphics);
	m_panelImage->Render(graphics);
}

void UIPauseMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Pause Menu View.");
	UIMenuView::Shutdown();

	delete m_panelImage;
	m_panelImage = nullptr;

	delete m_backgroundOverlayImage;
	m_backgroundOverlayImage = nullptr;
}

void UIPauseMenuView::TransitionIn(bool isAnimated)
{
	UIMenuView::TransitionIn(isAnimated);

	m_backgroundOverlayImage->SetActive(true);
	m_panelImage->SetActive(true);
}

void UIPauseMenuView::TransitionOut(bool isAnimated)
{
	UIMenuView::TransitionOut(isAnimated);

	if(isAnimated) return;

	m_backgroundOverlayImage->SetActive(false);
	m_panelImage->SetActive(false);
}

void UIPauseMenuView::OnCancelPressed()
{
	Continue();
}

void UIPauseMenuView::DoTransition(float deltaTime)
{
	UIMenuView::DoTransition(deltaTime);

	m_backgroundOverlayImage->SetAlpha(m_lerpedAlpha * 0.4f);
	m_panelImage->SetAlpha(m_lerpedAlpha);
}

void UIPauseMenuView::Continue()
{
	GameStateManager::Instance()->SwitchState("Gameplay");
}

void UIPauseMenuView::ProceedToOptionsView()
{
	GameStateManager::Instance()->SwitchState("SharedOptions");
}

void UIPauseMenuView::ShowQuitToMenuPrompt()
{
	// @TODO: Show Quit Prompt
}

void UIPauseMenuView::ShowQuitToDesktopPrompt()
{
	// @TODO Show Quit Prompt
}
