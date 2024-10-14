#include "UIManager.h"

#include "Logger.h"
#include "UISystemView.h"
#include "UIView.h"
#include "GlobalConstants.h"

using namespace GlobalConstants;

UIManager* UIManager::s_instance = nullptr;

UIManager::UIManager() :
	m_uiSystemView(nullptr),
	m_viewList(0)
{
}

UIManager::~UIManager()
{
	Shutdown();
}

void UIManager::Init()
{
	Logger::LogInfo("Initialising UI Manager.");
	s_instance = new UIManager;
}

void UIManager::Update(float deltaTime)
{
	s_instance->m_uiSystemView->Update(deltaTime);

	if(s_instance->m_uiSystemView->IsFading()) return;

	s_instance->UpdateUIViews(deltaTime);
	s_instance->SwitchState();
}

bool UIManager::AnyViewsInState(UIView::ViewState state)
{
	for(auto it = s_instance->m_viewList.begin(); it != s_instance->m_viewList.end(); ++it)
	{
		if((*it)->GetCurrentState() == state) return true;
	}

	return false;
}

void UIManager::UpdateUIViews(float deltaTime)
{
	for(auto it = s_instance->m_viewList.begin(); it != s_instance->m_viewList.end(); ++it)
	{
		if((*it)->GetCurrentState() == s_instance->m_currentViewState)
			(*it)->Update(deltaTime);
	}
}

void UIManager::SwitchState()
{
	if(s_instance->AnyViewsInState(s_instance->m_currentViewState)) return;

	m_currentViewState = m_targetViewState;
}

void UIManager::Render(Graphics* graphics)
{
	s_instance->m_uiSystemView->Render(graphics);

	for(auto it = s_instance->m_viewList.begin(); it != s_instance->m_viewList.end(); ++it)
	{
		(*it)->Render(graphics);
	}
}

void UIManager::CreateUISystemView()
{
	s_instance->m_uiSystemView = new UISystemView();
	s_instance->m_uiSystemView->Init("UI System View");
}

void UIManager::RegisterUIView(UIView* uiView)
{
	Logger::LogInfo(fmt::format("Registering {} with UI Manager.", uiView->GetName()));

	auto it = std::find(s_instance->m_viewList.begin(), s_instance->m_viewList.end(), uiView);

	if(it != s_instance->m_viewList.end()) 
		return;
	
	s_instance->m_viewList.push_back(uiView);
}

void UIManager::UnregisterUIView(UIView* uiView)
{
	Logger::LogInfo(fmt::format("Unregistering {} with UI Manager.", uiView->GetName()));

	auto it = std::find(s_instance->m_viewList.begin(), s_instance->m_viewList.end(), uiView);

	if(it == s_instance->m_viewList.end())
		return;

	s_instance->m_viewList.erase(it);
}

void UIManager::OnGameStateChange(std::string nextState)
{	
	std::string currentViewState;
	std::string targetViewState = "Visible";

	for(auto it = s_instance->m_viewList.begin(); it != s_instance->m_viewList.end(); ++it)
	{
		auto assignedStates = (*it)->GetAssignedStates();

		if(assignedStates.size() == 0) continue;

		auto result = std::find_if(
			assignedStates.begin(),
			assignedStates.end(),
			[nextState](const auto& state) { return state == nextState; });

		if(result == assignedStates.end())
		{
			if((*it)->IsActive()) (*it)->TransitionOut(true);
			s_instance->m_currentViewState = UIView::ViewState::AnimatingOut;
			currentViewState = "Animating Out";
			continue;
		}

		(*it)->TransitionIn(true);

		if(s_instance->m_currentViewState == UIView::ViewState::AnimatingOut)
		{
			s_instance->m_targetViewState = UIView::ViewState::AnimatingIn;
			targetViewState = "Animating Out";
		}
		else
		{
			s_instance->m_currentViewState = UIView::ViewState::AnimatingIn;
			s_instance->m_targetViewState = UIView::ViewState::Visible;
			currentViewState = "Animating In";
		}
	}

	Logger::LogInfo(fmt::format("UI Manager current view state: {}.", currentViewState));
	Logger::LogInfo(fmt::format("UI Manager target view state: {}.", targetViewState));
}

void UIManager::FadeOut()
{
	s_instance->m_uiSystemView->FadeOut();
}

void UIManager::FadeIn()
{
	s_instance->m_uiSystemView->FadeIn();
}

bool UIManager::IsFading()
{
	return s_instance->m_uiSystemView->IsFading();
}

void UIManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void UIManager::Shutdown()
{
	Logger::LogInfo("Shutting down UI Manager.");

	delete m_uiSystemView;
	m_uiSystemView = nullptr;
}