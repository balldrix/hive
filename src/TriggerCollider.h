#pragma once

#include "Collider.h"
#include "Sprite.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

enum class TriggerType
{
	AmbientSpawner = 0,
	CombatZoneSpawner = 1
};

struct TriggerColliderData
{
	std::string combatZoneId;
	std::vector<std::string> spawnerIds;
};

class TriggerCollider : public Collider
{
public:
	TriggerCollider();
	~TriggerCollider();

	void Init(TriggerType type, TriggerColliderData data);
	TriggerType GetType() const { return m_triggerType; }
	std::string GetCombatZoneId() const { return m_data.combatZoneId; }
	std::vector<std::string> GetSpawnerIds() const { return m_data.spawnerIds; }

private:
	TriggerType m_triggerType;
	TriggerColliderData m_data;
};