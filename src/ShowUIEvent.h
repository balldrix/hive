#pragma once

#include "IEvent.h"

class UIManager;

class ShowUIEvent : public IEvent
{
public:
	ShowUIEvent(UIManager* uiManager);
	~ShowUIEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	UIManager* m_uiManager;
	bool m_show;
};