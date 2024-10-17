#include "UITitleScreenView.h"

#include "UISpriteText.h"
#include "UIManager.h"
#include "Logger.h"
#include "UIConfig.h"

UITitleScreenView::UITitleScreenView() :
	m_startGameText(nullptr)
{
}

UITitleScreenView::~UITitleScreenView()
{
	Shutdown();
}

void UITitleScreenView::Init(std::string name)
{
	m_name = name;
	m_startGameText = new UISpriteText();
	m_startGameText->Init(UIConfig::DespairFont12);

	UIManager::RegisterUIView(this);
}

void UITitleScreenView::Render(Graphics* graphics)
{
	m_startGameText->Render(graphics);
}


void UITitleScreenView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Title Screen View");

	UIManager::UnregisterUIView(this);

	delete m_startGameText;
	m_startGameText = nullptr;
}
