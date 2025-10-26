#include "ShowUIEvent.h"

#include "IEvent.h"
#include "Logger.h"
#include "UIManager.h"
#include "UIView.h"

#include <variant>

ShowUIEvent::ShowUIEvent(UIManager* uiManager) :
	IEvent(),
	m_uiManager(uiManager),
	m_show(false)
{
}

ShowUIEvent::~ShowUIEvent()
{
}

void ShowUIEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<bool>(arg))
	{
		Logger::LogError("[ShowUIEvent] [OnStart] Incorrect argument, needs bool");
		return;
	}

	m_show = std::get<bool>(arg);
	m_uiManager->ShowUI(m_show);
	m_hasStarted = true;
	m_isComplete = false;
}

void ShowUIEvent::OnUpdate(float deltaTime)
{
	UIView* hudView = m_uiManager->GetView("UI Hud View");
	if(hudView->IsAnimating()) return;

	m_isComplete = true;
}
