#include "LevelCollision.h"

#include "Collider.h"
#include "Logger.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

LevelCollision* LevelCollision::s_instance = nullptr;

LevelCollision::LevelCollision() :
	m_colliders()
{
}

LevelCollision::~LevelCollision()
{
}

void LevelCollision::Init()
{
	s_instance = new LevelCollision;
}

void LevelCollision::Shutdown()
{
	delete s_instance;
	s_instance = nullptr;
}

void LevelCollision::AddCollider(std::string id, Collider box)
{
	if(s_instance->m_colliders.contains(id))
	{
		Logger::LogWarning(fmt::format("[Level Collision] Collision map already contains Collider with id {}", id));
		return;
	}
		
	s_instance->m_colliders[id] = box;
}

void LevelCollision::RemoveCollider(std::string id)
{
	s_instance->m_colliders.erase(id);
}

Collider* LevelCollision::GetCollider(std::string id)
{
	if(!s_instance->m_colliders.contains(id))
	{
		Logger::LogWarning(fmt::format("[Level Collision] Collider with id {} does not exist", id));
		return nullptr;
	}

	return &s_instance->m_colliders[id];
}

void LevelCollision::ClearAll()
{
	s_instance->m_colliders.clear();
}

bool LevelCollision::IsCollision(Collider box)
{
	for(auto it = s_instance->m_colliders.begin(); it != s_instance->m_colliders.end(); it++)
	{ 
		if(!(*it).second.OnCollision(box)) continue;

		return true;
	}

	return false;
}

bool LevelCollision::IsCollision(Vector2 position)
{
	for(auto it = s_instance->m_colliders.begin(); it != s_instance->m_colliders.end(); it++)
	{
		if(!(*it).second.OnCollision(position)) continue;

		return true;
	}

	return false;
}
