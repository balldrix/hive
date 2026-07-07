#include "UIMainView.h"

#include "Input.h"
#include "Logger.h"
#include "UIGameOverView.h"
#include "UIHudView.h"
#include "UIPauseMenuView.h"
#include "UIScreenFlashFX.h"
#include "UIView.h"

#include <string>

UIMainView::UIMainView() :
	m_uiHudView(nullptr),
	m_screenFlashFX(nullptr),
	m_uiPauseMenuView(nullptr),
	m_uiGameOverView(nullptr)
{
}

UIMainView::~UIMainView()
{
	Shutdown();
}

void UIMainView::Init(std::string name, Input* input)
{
	Logger::LogInfo("Initialising UI Main View");

	m_name = name;

	m_uiHudView = new UIHudView();
	m_uiHudView->Init("UI Hud View");
	m_uiHudView->TransitionOut(false);

	m_screenFlashFX = new UIScreenFlashFX();
	m_screenFlashFX->Init("UI Screen Flash FX");
	m_screenFlashFX->TransitionOut(false);

	m_uiPauseMenuView = new UIPauseMenuView();
	m_uiPauseMenuView->Init("UI Pause Menu View", input);
	m_uiPauseMenuView->TransitionOut(false);

	m_uiGameOverView = new UIGameOverView();
	m_uiGameOverView->Init("UI Game Over View", input);
	m_uiGameOverView->TransitionOut(false);
}

void UIMainView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Main View");

	delete m_uiGameOverView;
	m_uiGameOverView = nullptr;

	delete m_uiPauseMenuView;
	m_uiPauseMenuView = nullptr;

	delete m_screenFlashFX;
	m_screenFlashFX = nullptr;

	delete m_uiHudView;
	m_uiHudView = nullptr;
}
