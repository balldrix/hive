#include "UIPromptView.h"

#include "GlobalConstants.h"
#include "Input.h"
#include "Logger.h"
#include "UIConfig.h"
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UIPanelContainer.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"

#include "Frame.h"
#include "Graphics.h"
#include "LoadingGameState.h"
#include "UISpriteText.h"
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace GlobalConstants;

UIPromptView::UIPromptView() :
	m_panelContainer(nullptr),
	m_message(nullptr),
	m_parent(nullptr),
	m_promptType(PromptType::QuitToMenu),
	onCancel(nullptr)
{
}

UIPromptView::~UIPromptView()
{
	Shutdown();
}

void UIPromptView::Init(std::string name, UIMenuView* parent, Input* input)
{
	m_parent = parent;
	Logger::LogInfo("Initialising UI Prompt View");
	int x = static_cast<int>(GameWidth / 2.0f) - 55.0f;
	int y = static_cast<int>(GameHeight / 2.0f) - 25.0f;

	m_name = name;
	m_panelContainer = new UIPanelContainer();
	m_panelContainer->Init("Prompt Panel", RECT{ 0, 0, 110, 50 });
	m_panelContainer->SetPosition(Vector2(x, y));
	m_panelContainer->SetDepth(0.8f);

	m_message = new UISpriteText();
	m_message->Init(UIConfig::DespairFont8);
	m_message->SetAlignment(UISpriteText::Alignments::Centre);
	m_message->SetText("Quit To Menu?");
	m_message->SetDepth(0.95f);
	m_message->SetPosition(Vector2(static_cast<int>(GameWidth / 2.0f), y + 10));

	m_uiStackingView.Init("Quit Prompt Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Horizontal);

	m_menuOptions.emplace_back(new MenuOptionBase("Yes", OnConfirm));
	m_menuOptions.emplace_back(new MenuOptionBase("No", OnCancel));

	this->onCancel = onCancel;

	for(const auto& option : m_menuOptions)
	{
		std::string name = option->label;
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(name, input);
		item->SetText(name);
		item->SetDepth(0.9f);
		item->SetSelectedStateColours(Colors::White.v, Colors::SlateGray.v, Colors::Black.v);
		item->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
		m_uiStackingView.AddView(item);
	}

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

	Frame promptFrame;
	promptFrame.x = x + 30;
	promptFrame.y = y + 35;
	promptFrame.width = 200;
	promptFrame.height = 50;

	m_uiStackingView.UpdateLayout(promptFrame);
}

void UIPromptView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_message->Render(graphics);
	UIMenuView::Render(graphics);
	m_panelContainer->Render(graphics);
}

void UIPromptView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Prompt View");

	UIMenuView::Shutdown();

	delete m_panelContainer;
	m_panelContainer = nullptr;
}

void UIPromptView::TransitionIn(bool isAnimated)
{
	UIMenuView::TransitionIn(isAnimated);

	m_panelContainer->SetActive(true);
	m_message->SetActive(true);
}

void UIPromptView::TransitionOut(bool isAnimated)
{
	UIMenuView::TransitionOut(isAnimated);

	if(!isAnimated) {
		m_panelContainer->SetActive(false);
		m_message->SetActive(false);
		return;
	}

	m_panelContainer->SetOverlayAlpha(m_lerpedAlpha);
	m_panelContainer->SetPanelAlpha(m_lerpedAlpha);
}

void UIPromptView::OnCancelPressed()
{
	TransitionOut(false);
	m_parent->TransitionIn(false);
	m_parent->Focus();
}

void UIPromptView::SetMessage(std::string message)
{
	m_message->SetText(message);
	m_message->SetAlignment(UISpriteText::Alignments::Centre);
}

void UIPromptView::SetType(PromptType promptType)
{
	m_promptType = promptType;
}

void UIPromptView::DoTransition(float deltaTime)
{
	UIMenuView::DoTransition(deltaTime);

	m_panelContainer->SetPanelAlpha(m_lerpedAlpha);
	m_panelContainer->SetOverlayAlpha(m_lerpedAlpha);
	
}

void UIPromptView::OnConfirm(UIMenuView* owner)
{
	UIPromptView* promptView = static_cast<UIPromptView*>(owner);

	if(!promptView) return;

	PromptType promptType = promptView->GetType();

	if(promptType == UIPromptView::PromptType::QuitToMenu)
	{
		LoadingGameState::s_isloadingFromMainGameplayToFrontend = true;
		LoadingGameState::ProceedToFrontEnd();
	}
	else
	{
		PostQuitMessage(0);
	}
}

void UIPromptView::OnCancel(UIMenuView* owner)
{
	owner->OnCancelPressed();
}
