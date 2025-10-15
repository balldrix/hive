#include "DustFXEvent.h"

#include "GameObject.h"
#include "IEvent.h"
#include "SpriteFx.h"

DustFXEvent::DustFXEvent(GameObject* owner) :
	IEvent(),
	m_owner(owner)
{
}

void DustFXEvent::OnStart(EventArgument arg)
{
	m_hasStarted = true;
	m_isComplete = false;
	m_owner->DisplayDust(m_owner->GetGroundPosition());
}

void DustFXEvent::OnUpdate(float deltaTime)
{
	if(m_owner->GetDustFX()->IsActive()) return;
	m_isComplete = true;
}
