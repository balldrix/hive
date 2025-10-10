#include "MovePlayerEvent.h"

#include "IEvent.h"
#include "LevelCollision.h"
#include "Logger.h"
#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <variant>

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
	Vector2 newPosition = m_player->GetPosition() += offset;
	Vector2 newGroundPosition = m_player->GetGroundPosition() += offset;
	if(LevelCollision::IsCollision(newPosition) || LevelCollision::IsCollision(newGroundPosition)) return;

	m_player->SetPosition(newPosition);
	m_player->SetGroundPosition(newGroundPosition);
	m_isComplete = true;
}

void MovePlayerEvent::Reset()
{
	IEvent::Reset();
	m_distance = 0.0f;
}