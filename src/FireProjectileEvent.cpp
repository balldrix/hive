#include "FireProjectileEvent.h"

#include "Logger.h"
#include "RangedEnemy.h"

FireProjectileEvent::FireProjectileEvent(RangedEnemy* enemy) :
	IEvent(),
	m_enemy(enemy)
{
}

void FireProjectileEvent::OnStart(EventArgument arg)
{
	if(m_enemy == nullptr)
	{
		Logger::LogError("[FireProjectileEvent] [OnStart] Missing ranged enemy.");
		return;
	}

	m_enemy->FireProjectile();
	m_hasStarted = true;
	m_isComplete = true;
}

void FireProjectileEvent::OnUpdate(float deltaTime)
{
}
