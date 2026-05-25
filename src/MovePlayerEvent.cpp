#include "MovePlayerEvent.h"

#include "Collider.h"
#include "Enemy.h"
#include "HitBoxManager.h"
#include "IEvent.h"
#include "LevelCollision.h"
#include "Logger.h"
#include "NPCManager.h"
#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <variant>

namespace
{
	bool IsBlockedByEnemy(Player* player, const Vector2& position)
	{
		NPCManager* npcManager = NPCManager::Instance();
		if(npcManager == nullptr) return false;

		Collider playerPushBox = player->GetHitBoxManager()->GetPushBox();
		playerPushBox.Update(position);

		for(Enemy* enemy : npcManager->GetEnemyList())
		{
			if(enemy == nullptr || !enemy->IsActive() || enemy->IsDead()) continue;

			if(playerPushBox.OnCollision(enemy->GetHitBoxManager()->GetPushBox()))
			{
				return true;
			}
		}

		return false;
	}
}

MovePlayerEvent::MovePlayerEvent(Player* player) :
	IEvent(),
	m_player(player),
	m_distance(0.0f)
{
}

MovePlayerEvent::~MovePlayerEvent()
{
}

void MovePlayerEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<float>(arg))
	{
		Logger::LogError("[MovePlayerEvent] [OnStart] Incorrect argument, must be a float");
		return;
	}

	m_distance = std::get<float>(arg);
	m_hasStarted = true;
}

void MovePlayerEvent::OnUpdate(float deltaTime)
{
	Vector2 offset = m_player->GetFacingDirection() == Vector3::Right ? Vector2(m_distance, 0.0f) : Vector2(-m_distance, 0.0f);
	Vector2 newPosition = m_player->GetPosition() + offset;
	Vector2 newGroundPosition = m_player->GetGroundPosition() + offset;

	Collider playerPushBox = m_player->GetHitBoxManager()->GetPushBox();
	playerPushBox.Update(newPosition);

	if(LevelCollision::IsCollision(playerPushBox) || LevelCollision::IsCollision(newGroundPosition) ||
		IsBlockedByEnemy(m_player, newPosition))
	{
		m_isComplete = true;
		return;
	}

	m_player->SetPosition(newPosition);
	m_player->SetGroundPosition(newGroundPosition);
	m_isComplete = true;
}

void MovePlayerEvent::Reset()
{
	IEvent::Reset();
	m_distance = 0.0f;
}
