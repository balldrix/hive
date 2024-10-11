#include "UIManager.h"

#include "Logger.h"
#include "UISystemView.h"
#include "GlobalConstants.h"

using namespace GlobalConstants;

UIManager* UIManager::s_instance = nullptr;

UIManager::UIManager() :
	m_uiSystemView(0)
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
}

void UIManager::Render(Graphics* graphics)
{
	s_instance->m_uiSystemView->Render(graphics);
}

void UIManager::CreateUISystemView()
{
	s_instance->m_uiSystemView = new UISystemView();
	s_instance->m_uiSystemView->Init();
}

void UIManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void UIManager::Shutdown()
{
	delete m_uiSystemView;
	m_uiSystemView = nullptr;
}